#include<stdio.h>
#include<stdlib.h>

int main()
{
	int data[7]  = {0};
	FILE *fp = NULL;
	
	fp = fopen("Jessica.dat", "rb");
	if(fp == NULL)
    	{
        	printf("Error in creating the file\n");
        	exit(1);
    	}
   
   	fread(data, sizeof(data), 1, fp);
	printf("Data = ");
	for(int i = 0; i < 7; i++)
	{
		printf("%d ", data[i]);
	}
	printf("\n");
    	
	fclose(fp);
    	
	return 0;
}
