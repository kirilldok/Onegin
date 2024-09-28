#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

#include "OneginIO.h"
#include "SoftAssert.h"
#include "wqsort.h"

int main(int argc, char* argv[])
{
    char fileName[FILENAME_MAX] = {};
    getFileName(argc, argv, fileName);
    struct Text Onegin = {0, 0, 0, 0};

    readFromFile(&Onegin, "Onegin.txt");
    WriteTextinFile(&Onegin, "Sorted.txt", "w+b");//makes new file Sorted.txt, writes original text in it

    wqsort(Onegin.lines, Onegin.nLines, sizeof(Onegin.nLines)*2, structCmpForwards);
    WriteTextinFile(&Onegin, "Sorted.txt", "a+b");//add forward sorted text in Sorted.txt
    printf("\nSorting forward done.\n");

    wqsort(Onegin.lines, Onegin.nLines, sizeof(Onegin.lines)*2, structCmpBackwards);
    WriteTextinFile(&Onegin, "Sorted.txt", "a+b");//add bacward sorted text in Sorted.txt
    printf("Backward sorting is done.\n");

    freeOnegin(Onegin.lines);
    fprintf(stderr, "Structure cleared\n");
    return 0;
}


