#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "OneginIO.h"
#include "SoftAssert.h"

void readFromFile(struct Text* text, const char* fileName)
{
    FILE* fp = fopen(fileName, "rb");
    if(fp == NULL)
    {
        perror("fopen()");
        errParse(FOPEN_ERROR);
    } 

    fseek(fp, 0L, SEEK_END);
    text->bufferLen = ftell(fp);
    rewind(fp);

    FILE* db = fopen("debug.txt", "w+b");

    fprintf(stderr, "bufferLen = %d\n", text->bufferLen);

    text->buffer = (char*)calloc(text->bufferLen + 1, sizeof(char)); 
    if(text->buffer == NULL)
    {
        perror("callocl()");
        errParse(CALLOC_ERROR);
    }
    text->buffer[text->bufferLen] = '\n';

    if(fread(text->buffer, text->bufferLen, sizeof(*text->buffer), fp) == NULL)
    {
        perror("fread()");
        errParse(FREAD_ERROR);
    }


    for(int i = 0; i < text->bufferLen + 1; i++)
    {
        if(strchr(text->buffer + i + 1, '\n') != NULL)
        {
            i += strchr(text->buffer + i + 1, '\n') - (text->buffer + i);                
            text->nLines++;        
        }
    }

    fprintf(stderr, "nlines = %d\n", text->nLines);

    text->lines = (struct Line*)calloc(text->nLines + 1, sizeof(text->lines)*2);

    if(text->lines == NULL)
    {
        perror("callocl()");
        errParse(CALLOC_ERROR);
    }

    int ptrIndex = 0;

    for(size_t i = 0; i < text->bufferLen + 1; i++)
    {
        char* stringEndPtr =  strchr(text->buffer + i, '\n');
        if(stringEndPtr != NULL)
        {
            *stringEndPtr = '\0';
            size_t len = stringEndPtr - (text->buffer + i);
            text->lines[ptrIndex].ptr = text->buffer + i;
            i += len;

            text->lines[ptrIndex].length = len;
            fprintf(db, "%zu\n", text->lines[ptrIndex].length);
            ptrIndex++;
            assert(ptrIndex*sizeof(struct Line*) <= ((text->nLines + 1) * sizeof(text->lines)));
        }
    }
    fprintf(stderr, "%zu\n", ptrIndex);
    fclose(db);
    fclose(fp);
}

void freeOnegin(struct Line* lines)
{
    free(lines);
}

int getFileName(int c, char** v, char* fName)
{
    char defName [11] = "Onegin.txt";
    if(c == 2)
    {
        fName = v[1];
        return 0;
    }
    else if(c > 2)
    {
        fprintf(stderr, "Too many console arguments, all will be ignored.\n");
        fName = defName;
        return TOO_MANY_CARGS;
    }
    else
    {
        fName = defName;
        return 0;
    }
}

void errParse(int code)
{   
    switch(code)
    {
        case FREAD_ERROR:
        {
            fprintf(stderr, "Please, check for file's acces settings.");
            exit(1);
        }
        
        case FOPEN_ERROR: 
        {
            fprintf(stderr, "Please, check for correctness of file's name.");
            exit(2);
        }

        case TOO_MANY_CARGS:
        {
            fprintf(stderr, "Please, enter only one flag. It should be the name of the file you need to sort.");
            exit(3);
        }

        case CALLOC_ERROR:
        {
            fprintf(stderr, "No accesible memory.");
            exit(4);
        }

        default:
        {
            break;
        }
    }
}