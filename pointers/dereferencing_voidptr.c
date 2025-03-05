#include<stdio.h>

int main()
{
	void *vdata;

	int idata = 10;
	char cdata = 'J';
	float fdata = 27.9;

	vdata = &idata;
	//printf("*vdata = %d\n", *vdata);  will give error because I have not typecasted.
	printf("idata = %d\n", *(int*)vdata);

	vdata = &cdata;
	printf("cdata = %c\n", *(char*)vdata);

	vdata = &fdata;
	printf("fdata = %.2f\n", *(float*)vdata);

	return 0;
}  //this program shows that void pointer can be reused to store addresses of multiple variables
