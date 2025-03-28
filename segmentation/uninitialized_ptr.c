#include<stdio.h>

int main()
{
	int *ptr;
	*ptr = 20; //dereferencing a pointer that is uninitialized
	printf("ptr = %d\n", *(int*)ptr);

	return 0;
}



//you cannot dereference a pointer to an integer directly....it has to point to an address....and dereferencing will give the value at that address
