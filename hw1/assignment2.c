#include <stdio.h> 

int main(){
	int arr[5] = {10, 20, 30 , 40, 50};
	int *p = arr;

	printf("original arr:\n");

	for(int i = 0; i < 5; i++){
		printf("%d ", *(p + i));
	}

	printf("modified arr:\n");

	for(int i = 0; i < 5; i++){
		*(p + i) = *(p + i) + 5;
		printf("%d ", *(p + i));
	}

	printf("\nUsing arr name:\n");

	for(int i = 0; i < 5; i++){
		printf("%d ", arr[i]);
	}

	return 0;
}

