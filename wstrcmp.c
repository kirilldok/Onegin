#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "SoftAssert.h"
#include "OneginIO.h"

int strcmpForwards(const void* a, const void* b)
{
    size_t aIndex = 0;
    size_t bIndex = 0;
    while(*(*((char**)a) + aIndex) != '\0' && *(*((char**)b) + bIndex) != '\0')
    {
        if(isalpha(*(*((char**)a) + aIndex)) || *(*((char**)a) + aIndex) == '\0')
        {

            if(isalpha(*(*((char**)b) + bIndex)) || *(*((char**)b) + bIndex) == '\0')
            {
                if(tolower(*(*((char**)a) + aIndex)) - tolower(*(*((char**)b) + bIndex)) > 0)
                {
                    return 1;
                }

                else if(tolower(*(*((char**)a) + aIndex)) - tolower(*(*((char**)b) + bIndex)) < 0)
                {
                    return -1; 
                }

                else
                {
                    bIndex++;
                    aIndex++;
                } 
            }
            else
                bIndex++;
        }
        else 
            aIndex++;
    }
    return 0;
}

int strcmpBackwards(const void* a, const void* b)
{
    size_t bIndex = 0;
    int aIndex = 0;
    
    int aSize = aIndex = strchr(*((char**)a), '\0') - *((char**)a);
    int bSize = bIndex = strchr(*((char**)b), '\0') - *((char**)b);

    while(bIndex > 0  && aIndex > 0)
    {
        if(isalpha(*(*((char**)a) + aIndex)) || *(*((char**)a) + aIndex) == '\0')
        {
            if(isalpha(*(*((char**)b) + bIndex)) || *(*((char**)b) + bIndex) == '\0')
            {
                if(tolower(*(*((char**)a) + aIndex)) - tolower(*(*((char**)b) + bIndex)) > 0)
                    return 1;
                else if(tolower(*(*((char**)a) + aIndex)) - tolower(*(*((char**)b) + bIndex)) < 0)
                    return -1;
                else
                {
                    bIndex--;
                    aIndex--;
                } 
            }
            else
                bIndex--;
        }
        else 
            aIndex--;
    }
    
    return 0;

} 