#include <stdlib.h>
#include <string.h>

#include "wqsort.h"
#include "SoftAssert.h"

void wqsort(void* ptr, size_t count, size_t size, compar_t comp)
{
    
    char* cptr = (char*) ptr;
    if(count <= 1)
    {
        return;
    }

    size_t upper = 0;
    size_t lower = 0;

    while(upper < count)
    {
        while(comp(cptr + upper*size, cptr + (count - 1)*size) > 0 && upper < count)
        {
            upper++;
        }
        while((comp(cptr + lower*size, cptr + (count - 1)*size) < 0 || comp(cptr + lower*size, cptr + (count - 1)*size) == 0) && lower < upper)
        {
            lower++; 
        }

        swapObjects(cptr + lower*size, cptr + upper*size, size);

        upper++;
    }

    wqsort((char*)ptr, lower, size, comp);
    wqsort(((char*)ptr + (lower + 1)*size), count - lower - 1, size, comp);
}
