
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

static int write_all(int fd, const char *buf, size_t len) {
    size_t done = 0;

    while (done < len) {
        ssize_t n = write(fd, buf + done, len - done);
        if (n == -1 && errno == EINTR) continue;
        if (n <= 0) return -1;
        done += (size_t)n;
    }

    return 0;
}

static int read_char(int fd, char *ch) {
    ssize_t n;

    do {
        n = read(fd, ch, 1);
    } while (n == -1 && errno == EINTR);

    if (n == -1) perror("read");
    if (n == 0) fprintf(stderr, "Unexpected end of file\n");

    return n == 1 ? 0 : -1;
}

int main(void) {
    int fd = open("numbers.txt",
                  O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write numbers from 1 to 10.
    for (int i = 1; i <= 10; i++) {
        char line[16];
        int len = snprintf(line, sizeof(line), "%d\n", i);

        if (len < 0 ||
            write_all(fd, line, (size_t)len) == -1) {
            perror("write numbers");
            close(fd);
            return 1;
        }
    }

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    fd = open("numbers.txt", O_RDWR);

    if (fd == -1) {
        perror("open again");
        return 1;
    }

    // Find line 4 by counting the first three newlines.
    int newlines = 0;
    char ch;

    while (newlines < 3) {
        if (read_char(fd, &ch) == -1) {
            close(fd);
            return 1;
        }

        if (ch == '\n') newlines++;
    }

    off_t line4_start = lseek(fd, 0, SEEK_CUR);

    if (line4_start == (off_t)-1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    // Skip old line 4.
    do {
        if (read_char(fd, &ch) == -1) {
            close(fd);
            return 1;
        }
    } while (ch != '\n');

    off_t rest_start = lseek(fd, 0, SEEK_CUR);
    off_t end = lseek(fd, 0, SEEK_END);

    if (rest_start == (off_t)-1 || end == (off_t)-1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    size_t rest_size = (size_t)(end - rest_start);
    char *rest = malloc(rest_size ? rest_size : 1);

    if (rest == NULL) {
        perror("malloc");
        close(fd);
        return 1;
    }

    // Read all remaining lines into memory.
    if (lseek(fd, rest_start, SEEK_SET) == (off_t)-1) {
        perror("lseek");
        free(rest);
        close(fd);
        return 1;
    }

    size_t loaded = 0;

    while (loaded < rest_size) {
        ssize_t n = read(fd, rest + loaded,
                         rest_size - loaded);

        if (n == -1 && errno == EINTR) continue;

        if (n <= 0) {
            if (n == -1) perror("read remainder");
            else fprintf(stderr, "Unexpected EOF\n");

            free(rest);
            close(fd);
            return 1;
        }

        loaded += (size_t)n;
    }

    // Replace line 4 with 100 and then write the remainder.
    if (lseek(fd, line4_start, SEEK_SET) == (off_t)-1) {
        perror("lseek");
        free(rest);
        close(fd);
        return 1;
    }

    if (write_all(fd, "100\n", 4) == -1 ||
        write_all(fd, rest, rest_size) == -1) {
        perror("write replacement");
        free(rest);
        close(fd);
        return 1;
    }

    free(rest);

    if (ftruncate(fd, line4_start + 4 + (off_t)rest_size) == -1) {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    // Return to the beginning and print the final contents.
    if (lseek(fd, 0, SEEK_SET) == (off_t)-1) {
        perror("rewind");
        close(fd);
        return 1;
    }

    printf("Final file content:\n");
    fflush(stdout);

    char buffer[128];

    while (1) {
        ssize_t n = read(fd, buffer, sizeof(buffer));

        if (n == 0) break;
        if (n == -1 && errno == EINTR) continue;

        if (n == -1) {
            perror("read");
            close(fd);
            return 1;
        }

        if (write_all(STDOUT_FILENO, buffer, (size_t)n) == -1) {
            perror("write stdout");
            close(fd);
            return 1;
        }
    }

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
