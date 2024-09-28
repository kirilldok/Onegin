#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "SoftAssert.h"
#include "OneginIO.h"

int structCmpForwards(const void* a, const void* b)
{
    size_t aIndex = 0;
    size_t bIndex = 0;
    struct Line* aStruct = (struct Line*)a;
    struct Line* bStruct = (struct Line*)b;

    while(aStruct->length > aIndex && bStruct->length > bIndex)
    {
        if(isalpha(*(aStruct->ptr + aIndex)) || *(aStruct->ptr + aIndex) == '\0')
        {
            if(isalpha(*(bStruct->ptr + bIndex)) || *(bStruct->ptr + bIndex) == '\0')
            {
                if(tolower(*(aStruct->ptr + aIndex)) - tolower(*(bStruct->ptr + bIndex)) !=  0)
                {
                    return tolower(*(aStruct->ptr + aIndex)) - tolower(*(bStruct->ptr + bIndex));
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

int structCmpBackwards(const void* a, const void* b)
{
    struct Line* aStruct = (struct Line*)a;
    struct Line* bStruct = (struct Line*)b;
    size_t aIndex = aStruct->length;
    size_t bIndex = bStruct->length;
    
    while(aIndex > 0 && bIndex > 0)
    {
        if(isalpha(*(aStruct->ptr + aIndex)) || *(aStruct->ptr + aIndex) == '\0')
        {
            if(isalpha(*(bStruct->ptr + bIndex)) || *(bStruct->ptr + bIndex) == '\0')
            {
                if(tolower(*(aStruct->ptr + aIndex)) - tolower(*(bStruct->ptr + bIndex)) !=  0)
                {
                    return tolower(*(aStruct->ptr + aIndex)) - tolower(*(bStruct->ptr + bIndex));
                }

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