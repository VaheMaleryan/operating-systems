#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;

    printf("Enter how many students: ");
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));

    if (a == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter the marks of student %d: ", i + 1);
        scanf("%d", &a[i]);
    }

    int max = a[0];
    int min = a[0];

    for (int i = 1; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
        }

        if (a[i] < min) {
            min = a[i];
        }
    }

    printf("Maximum marks: %d\n", max);
    printf("Minimum marks: %d\n", min);

    free(a);

    return 0;
}