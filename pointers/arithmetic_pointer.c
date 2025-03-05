#include<stdio.h>

int main()
{
        int adata[3] = {0};

        void *vdata = &adata[0];

        printf("For Integer type:\n");
        printf("vdata = %p\n", vdata);
        printf("vdata + 1 = %p\n\n", (int*)vdata + 1);

        printf("For character type:\n");
        printf("vdata = %u\n", vdata);
        printf("vdata + 1 = %u\n\n", (char*)vdata + 1);

        return 0;
}

