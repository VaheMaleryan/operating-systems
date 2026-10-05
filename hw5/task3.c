#include "stdio.h"
#include "stdlib.h"

int main() {
    int n;
    n = 10;

    int *a = malloc(n * sizeof(int));

    if (a == NULL){
        return 1;
    }

    for( int i = 0 ; i< n; i++){
        printf("enter the element %d: ", i + 1);
        scanf("%d", &a[i]);
    }

    int *b = realloc(a, n/2 * sizeof(int));

    if (b == NULL){
        free(a);
        return 1;
    }

    for( int i = 0 ; i< n/2; i++){
        printf("element %d: %d\n", i + 1, b[i]);
    }

    free(b);
    return 0;
}