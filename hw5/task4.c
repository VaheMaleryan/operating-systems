#include <stdio.h>
#include <stdlib.h>

int main() {

    char **names = malloc(3 * sizeof(char *));

    if (names == NULL) {
        return 1;
    }

   
    for (int i = 0; i < 3; i++) {
        names[i] = malloc(50 * sizeof(char));

        if (names[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(names[j]);
            }

            free(names);
            return 1;
        }
    }

   
    for (int i = 0; i < 3; i++) {
        printf("Enter name %d: ", i + 1);
        scanf("%49s", names[i]);
    }

   
    for (int i = 0; i < 3; i++) {
        printf("Name %d: %s\n", i + 1, names[i]);
    }

   
    char **temp = realloc(names, 5 * sizeof(char *));

    if (temp == NULL) {
        for (int i = 0; i < 3; i++) {
            free(names[i]);
        }

        free(names);
        return 1;
    }

    names = temp;

    
    for (int i = 3; i < 5; i++) {
        names[i] = malloc(50 * sizeof(char));

        if (names[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(names[j]);
            }

            free(names);
            return 1;
        }
    }

    
    for (int i = 3; i < 5; i++) {
        printf("Enter name %d: ", i + 1);
        scanf("%49s", names[i]);
    }

    
    printf("All names:\n");

    for (int i = 0; i < 5; i++) {
        printf("Name %d: %s\n", i + 1, names[i]);
    }

    
    for (int i = 0; i < 5; i++) {
        free(names[i]);
    }

    
    free(names);

    return 0;
}