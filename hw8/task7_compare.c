
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

static ssize_t read_chunk(int fd, char *buf, size_t capacity) {
    ssize_t n;

    do {
        n = read(fd, buf, capacity);
    } while (n == -1 && errno == EINTR);

    return n;
}

int main(void) {
    char path1[256], path2[256];
    char a[4096], b[4096];

    printf("Enter first file path: ");
    fflush(stdout);

    if (fgets(path1, sizeof(path1), stdin) == NULL)
        return 1;

    path1[strcspn(path1, "\n")] = '\0';

    printf("Enter second file path: ");
    fflush(stdout);

    if (fgets(path2, sizeof(path2), stdin) == NULL)
        return 1;

    path2[strcspn(path2, "\n")] = '\0';

    int fd1 = open(path1, O_RDONLY);

    if (fd1 == -1) {
        perror("open first");
        return 1;
    }

    int fd2 = open(path2, O_RDONLY);

    if (fd2 == -1) {
        perror("open second");
        close(fd1);
        return 1;
    }

    ssize_t count1 = 0, count2 = 0;
    size_t pos1 = 0, pos2 = 0;
    long long index = 0;
    int result = 0;

    while (1) {
        if (pos1 == (size_t)count1) {
            count1 = read_chunk(fd1, a, sizeof(a));
            pos1 = 0;

            if (count1 == -1) {
                perror("read first");
                result = 1;
                break;
            }
        }

        if (pos2 == (size_t)count2) {
            count2 = read_chunk(fd2, b, sizeof(b));
            pos2 = 0;

            if (count2 == -1) {
                perror("read second");
                result = 1;
                break;
            }
        }

        if (count1 == 0 && count2 == 0) {
            printf("Files are identical\n");
            break;
        }

        if (count1 == 0 || count2 == 0) {
            printf("Files differ at byte %lld\n", index);
            result = 1;
            break;
        }

        size_t left1 = (size_t)count1 - pos1;
        size_t left2 = (size_t)count2 - pos2;
        size_t take = left1 < left2 ? left1 : left2;

        for (size_t i = 0; i < take; i++) {
            if (a[pos1 + i] != b[pos2 + i]) {
                printf("Files differ at byte %lld\n",
                       index + (long long)i);
                result = 1;
                goto finish;
            }
        }

        pos1 += take;
        pos2 += take;
        index += (long long)take;
    }

finish:
    if (close(fd1) == -1) {
        perror("close first");
        result = 1;
    }

    if (close(fd2) == -1) {
        perror("close second");
        result = 1;
    }

    return result;
}
