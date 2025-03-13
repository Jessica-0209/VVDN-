#include<stdio.h>

union test1
{
	int data;
	char ch;
} t1;

union test2
{
	int data1;
	int data2;
} t2;

union test3
{
	float data1;
	int data2;
} t3;

union test4
{
	char ch[24];
	int data;
} t4;

union test5
{
	char ch1;
	char ch2;
} t5;

int main()
{
	printf("Sizeof(t1) = %lu\n", sizeof(t1));
	printf("Sizeof(t2) = %lu\n", sizeof(t2));
	printf("Sizeof(t3) = %lu\n", sizeof(t3));
	printf("Sizeof(t4) = %lu\n", sizeof(t4));
	printf("Sizeof(t5) = %lu\n", sizeof(t5));

	return 0;
}
