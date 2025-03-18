#include<stdio.h>
#include<stdlib.h>

int main()
{
        int ch = 0;
        FILE *fp = NULL;

        fp = fopen("/home/vvsa/VVDN Git/VVDN-/file_handling/Jessica.txt", "w");
        if(fp == NULL)
        {
                printf("File not created!\n");
                exit(1);
        }

        for(ch = 97; ch <= 122; ch++)
        {
                fputc(ch, fp);
        }

        fclose(fp);

        printf("A to Z written to the created file!\n");

        return 0;
}

