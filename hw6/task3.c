#include <stdio.h>

struct Data0 {
    char a;
    int b;
    double c;
};

#pragma pack(push, 1)
struct Data1{
    char a;
    int b;
    double c;
};
#pragma pack(pop)

#pragma pack(push,2)
struct Data2{
    char a;
    int b;
    double c;
};
#pragma pack(pop)

#pragma pack(push,4)
struct Data3{
    char a;
    int b;
    double c;
};
#pragma pack(pop)


int main(){
    struct Data0 s0;
    struct Data1 s1;
    struct Data2 s2;
    struct Data3 s3;

      printf("Normal struct Data0 size: %zu bytes\n", sizeof(s0));
    printf("Address of char: %p\n", (void*)&s0.a);
    printf("Address of int: %p\n", (void*)&s0.b);
    printf("Address of double: %p\n", (void*)&s0.c);

    printf("\nPacked(1) struct Data1 size: %zu bytes\n", sizeof(s1));
    printf("Address of char: %p\n", (void*)&s1.a);
    printf("Address of int: %p\n", (void*)&s1.b);
    printf("Address of double: %p\n", (void*)&s1.c);

    printf("\nPacked(2) struct Data2 size: %zu bytes\n", sizeof(s2));
    printf("Address of char: %p\n", (void*)&s2.a);
    printf("Address of int: %p\n", (void*)&s2.b);
    printf("Address of double: %p\n", (void*)&s2.c);

    printf("\nPacked(4) struct Data4 size: %zu bytes\n", sizeof(s3));
    printf("Address of char: %p\n", (void*)&s3.a);
    printf("Address of int: %p\n", (void*)&s3.b);
    printf("Address of double: %p\n", (void*)&s3.c);

    return 0;

}