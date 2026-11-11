
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    char source[256], destination[256], buffer[1024];
    long long total = 0;
    int failed = 0;

    printf("Enter source file path: ");
    fflush(stdout);
    if (fgets(source, sizeof(source), stdin) == NULL) {
        fprintf(stderr, "Cannot read source path\n");
        return 1;
    }
    source[strcspn(source, "\n")] = '\0';

    printf("Enter destination file path: ");
    fflush(stdout);
    if (fgets(destination, sizeof(destination), stdin) == NULL) {
        fprintf(stderr, "Cannot read destination path\n");
        return 1;
    }
    destination[strcspn(destination, "\n")] = '\0';

    if (source[0] == '\0' || destination[0] == '\0' ||
        strcmp(source, destination) == 0) {
        fprintf(stderr, "Invalid paths or source equals destination\n");
        return 1;
    }

    int src = open(source, O_RDONLY);
    if (src == -1) {
        perror("open source");
        return 1;
    }

    int dst = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst == -1) {
        perror("open destination");
        close(src);
        return 1;
    }

    while (1) {
        ssize_t nread = read(src, buffer, sizeof(buffer));
        if (nread == 0) break;

        if (nread == -1) {
            if (errno == EINTR) continue;
            perror("read");
            failed = 1;
            break;
        }

        ssize_t written = 0;
        while (written < nread) {
            ssize_t n = write(dst, buffer + written,
                              (size_t)(nread - written));

            if (n == -1 && errno == EINTR) continue;

            if (n <= 0) {
                if (n == -1) perror("write");
                else fprintf(stderr, "write made no progress\n");
                failed = 1;
                break;
            }

            written += n;
            total += n;
        }

        if (failed) break;
    }

    if (close(src) == -1) {
        perror("close source");
        failed = 1;
    }
    if (close(dst) == -1) {
        perror("close destination");
        failed = 1;
    }

    if (failed) return 1;

    printf("Total bytes copied: %lld\n", total);
    return 0;
}
