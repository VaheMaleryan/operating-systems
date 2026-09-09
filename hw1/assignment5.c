#include <stdio.h> 

int main(){
	char str[] = "Hello";
	char *p = str;
	int count = 0;

	while(*p != '\0'){
		printf("%c", *p);
		p++;
		count++;
	}

	printf("\nLength: %d\n", count);

	return 0 ;

}
