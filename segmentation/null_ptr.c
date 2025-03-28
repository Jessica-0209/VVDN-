#include <stdio.h>
#include<stdlib.h>

int main() {
	int a = 10;
	void 	
	int *ptr = (int*)malloc(sizeof(int));	
	*ptr = a;
    	
	printf("%d\n", *ptr);

	free(ptr);
	//ptr = NULL;
	printf("%p\n", ptr);
	ptr = NULL;
	printf("%p\n", ptr);

    	return 0;
}
