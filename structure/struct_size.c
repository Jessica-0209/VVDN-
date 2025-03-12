#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char Name[12];
    int Age;
    float Weight;
    int RollNumber;
} student_info;

int main()
{
    student_info RamInfo[2] = {0};
    
    student_info *info  = NULL;
    int size_struct = 0;
    
    info = RamInfo;
    
    size_struct = (char*)(info + 1) - (char*)(info);
    printf("Size of structure  =  %d\n\n",size_struct);
    return 0;
}
