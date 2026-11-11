
#define _POSIX_C_SOURCE 200809L
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
    const char text[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int fd = open("data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (write_all(fd, text, strlen(text)) == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    fd = open("data.txt", O_RDWR);
    if (fd == -1) {
        perror("open again");
        return 1;
    }

    off_t size = lseek(fd, 0, SEEK_END);
    if (size == (off_t)-1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("Original size: %lld bytes\n", (long long)size);

    if (ftruncate(fd, 10) == -1) {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    size = lseek(fd, 0, SEEK_END);
    if (size == (off_t)-1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("New size: %lld bytes\n", (long long)size);

    if (lseek(fd, 0, SEEK_SET) == (off_t)-1) {
        perror("lseek to start");
        close(fd);
        return 1;
    }

    char buffer[64];
    ssize_t n;

    printf("Remaining content: ");
    fflush(stdout);

    while ((n = read(fd, buffer, sizeof(buffer))) != 0) {
        if (n == -1) {
            if (errno == EINTR) continue;
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

    printf("\n");

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
