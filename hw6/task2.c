#include <stdio.h>

struct Data0 {
    char a;
    int b;
    double c;
};

struct Data1{
    double c;
    int b;
    char a;

};

int main() {
    struct Data0 s0;
    struct Data1 s1;

    printf("Original struct Data0 size: %zu bytes\n", sizeof(s0));
    printf("adress of char: %p\n", &s0.a);
    printf("adress of int: %p\n", &s0.b);
    printf("adress of double: %p\n", &s0.c);

    printf("Reordered struct Data1 size: %zu bytes\n", sizeof(s1));
    printf("adress of double: %p\n", &s1.c);
    printf("adress of int: %p\n", &s1.b);
    printf("adress of char: %p\n", &s1.a);

    return 0;
    

}