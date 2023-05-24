#include "general.h"

void checkMemoryAllocationPos(checkersPos *pos)
{
    if (pos == NULL)
    {
        printf("Memory allocation error!!!\n");
        exit(1);
    }
}