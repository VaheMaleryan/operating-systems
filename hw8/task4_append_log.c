
#include <stdio.h>
#include <string.h>
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

int main(void) {
    int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    char line[1024];
    size_t len = 0;
    char ch;

    printf("Enter a log line: ");
    fflush(stdout);

    // Read one line using read(), not fgets().
    while (1) {
        ssize_t n = read(STDIN_FILENO, &ch, 1);

        if (n == -1 && errno == EINTR) continue;

        if (n == -1) {
            perror("read stdin");
            close(fd);
            return 1;
        }

        if (n == 0 || ch == '\n') break;

        if (len == sizeof(line)) {
            fprintf(stderr, "Line too long\n");
            close(fd);
            return 1;
        }

        line[len++] = ch;
    }

    char entry[1100];

    int prefix_len = snprintf(entry, sizeof(entry),
                              "PID=%ld: ", (long)getpid());

    if (prefix_len < 0 ||
        (size_t)prefix_len + len + 1 > sizeof(entry)) {
        fprintf(stderr, "Log entry too long\n");
        close(fd);
        return 1;
    }

    memcpy(entry + prefix_len, line, len);
    entry[prefix_len + len] = '\n';

    size_t entry_len = (size_t)prefix_len + len + 1;

    if (write_all(fd, entry, entry_len) == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    // O_APPEND moves the file offset to EOF before each write.
    // Therefore SEEK_CUR returns a growing offset after appending.
    off_t end = lseek(fd, 0, SEEK_CUR);

    if (end == (off_t)-1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("Final file offset: %lld\n", (long long)end);

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
