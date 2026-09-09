#include <stdio.h> 

int main(){
	int x = 10;
	int *p = &x;
	int **pp = &p;

	printf("using p: %d\n", *p);
	printf("using double p: %d\n", **pp);

	return 0;
}
