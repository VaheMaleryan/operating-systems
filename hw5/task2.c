#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int *a = calloc(n, sizeof(int));

    if (a == NULL) {
        return 1;
    }

    printf("Array after calloc: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    printf("Updated array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum += a[i];
    }

    double average = (double)sum / n;

    printf("Average of the array: %.1f\n", average);

    free(a);

    return 0;
}