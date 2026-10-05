#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("enter the number of element: ");
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));
    if (a == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("enter the element %d: ", i + 1);
        scanf("%d", &a[i]);
    }

    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum += a[i];
    }

    printf("sum of the elements: %d\n", sum);
    free(a);
    return 0;
}
    