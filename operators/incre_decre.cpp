//sample program just to show this is how we can use incre and decre in cpp

#include<cstdio>

int main()
{
	int data = 7;
	int &val = ++data;
	++data = 27;
	//val++ = 23;   invalid
	

	printf("data = %d\n", data);
	printf("val = %d\n", val);

	return 0;
}
