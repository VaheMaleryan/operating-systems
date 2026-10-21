#include <stdio.h>

int main(){
    char c;
    short s; 
    int i;
    double d;

    printf("Size of char: %zu byte\n", sizeof(c));
    printf("size of short: %zu bytes\n", sizeof(s));
    printf("size of int: %zu bytes\n", sizeof(i));
    printf("size of double: %zu bytes\n", sizeof(d));

    printf("address of char: %p\n", &c);
    printf("address of short: %p\n", &s);
    printf("address of int: %p\n", &i);
    printf("address of double: %p\n", &d);


}