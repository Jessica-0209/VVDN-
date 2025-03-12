#include <stdio.h>

void swap(int *a, int *b) 
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int main() 
{
    int x = 5, y = 10;

    printf("Before swapping:\n x = %d, y = %d\n", x, y);

    swap(&x, &y);
    
    printf("After swapping:\n x = %d, y = %d\n", x, y);

    return 0;
}





