#include <stdio.h>
#include<stdlib.h>

int main()
{
    FILE *fp = NULL;
    
    fp  = fopen ("/home/vvsa/VVDN Git/VVDN-/file_handling/data.txt", "w");
    if(fp == NULL)
    {
        printf("File is not created\n");
        exit(1);
    }
    else
    {
        printf("File is created\n");
    }
 
    fclose(fp);
    return 0;
}
