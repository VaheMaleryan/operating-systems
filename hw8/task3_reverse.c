
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    char path[256];

    printf("Enter file path: ");
    fflush(stdout);

    if (fgets(path, sizeof(path), stdin) == NULL) {
        fprintf(stderr, "Cannot read file path\n");
        return 1;
    }

    path[strcspn(path, "\n")] = '\0';

    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    off_t size = lseek(fd, 0, SEEK_END);
    if (size == (off_t)-1) {
        perror("lseek size");
        close(fd);
        return 1;
    }

    for (off_t pos = size; pos > 0; pos--) {
        char ch;

        if (lseek(fd, pos - 1, SEEK_SET) == (off_t)-1) {
            perror("lseek");
            close(fd);
            return 1;
        }

        ssize_t n;

        do {
            n = read(fd, &ch, 1);
        } while (n == -1 && errno == EINTR);

        if (n != 1) {
            if (n == -1) perror("read");
            else fprintf(stderr, "Unexpected end of file");
            close(fd);
            return 1;
        }

        do {
            n = write(STDOUT_FILENO, &ch, 1);
        } while (n == -1 && errno == EINTR);

        if (n != 1) {
            perror("write");
            close(fd);
            return 1;
        }
    }

    if (write(STDOUT_FILENO, "\n", 1) != 1) {
        perror("write newline");
        close(fd);
        return 1;
    }

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
