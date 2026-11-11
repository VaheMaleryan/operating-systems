
#include <stdio.h>
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
    int fd = open("sparse.bin",
                  O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (write_all(fd, "START", 5) == -1) {
        perror("write START");
        close(fd);
        return 1;
    }

    // Skip 1 MiB without writing zeros.
    // This creates a sparse hole.
    // Disk usage (du) is smaller because the filesystem
    // normally does not allocate disk blocks for the hole.
    if (lseek(fd, 1024 * 1024, SEEK_CUR) == (off_t)-1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    if (write_all(fd, "END", 3) == -1) {
        perror("write END");
        close(fd);
        return 1;
    }

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    fd = open("sparse.bin", O_RDONLY);

    if (fd == -1) {
        perror("reopen");
        return 1;
    }

    off_t size = lseek(fd, 0, SEEK_END);

    if (size == (off_t)-1) {
        perror("lseek size");
        close(fd);
        return 1;
    }

    printf("Apparent file size: %lld bytes\n", (long long)size);

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
