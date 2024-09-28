#ifndef ONEGIN_IO_INCLUDED
#define ONEGIN_IO_INCLUDED
#include <limits.h>
#include <string.h>
#include <stdio.h>

enum errors
{
    FREAD_ERROR = 1,
    FOPEN_ERROR,
    TOO_MANY_CARGS,
    CALLOC_ERROR,
};

struct Line
{
    char* ptr;
    size_t length;
};

struct Text
{
    char* buffer;
    size_t bufferLen;
    struct Line* lines;
    size_t nLines;
};

void errParse(int code);
int getFileName(int c, char** v, char* fName);
void readFromFile(struct Text* text, const char* const fileName);
void writeToFile(struct Text* sorted, const char* const fileName);
int strcmpForwards(const void* a, const void* b);
int strcmpBackwards(const void* a, const void* b);
int structCmpForwards(const void* a, const void* b);
int structCmpBackwards(const void* a, const void* b);
int WriteTextinFile(struct Text* text, const char* fName, const char* mode);
void freeOnegin(struct Line* lines);

#endif
