#include<stdio.h>

#define ELEMENT_SIZE(x) sizeof(x[0])
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

int compare_int(const void *a, const void *b)
{
	int x = *(const int *)a;
	int y = *(const int *)b;

	if (x < y)
	{
		return -1;
	}
	else if (x > y)
	{
		return 1;
	}
	return 0;
}

