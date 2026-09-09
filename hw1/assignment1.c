#include <stdio.h>

int main(){
	int x = 10;
	int *p = &x;

	printf("address of x: %p\n", &x);
	printf("address of x in p: %p\n", p);

	*p = 11;

	printf("new value od x: %d\n", x);

	return 0;

}
