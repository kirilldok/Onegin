#include "OneginIO.h"

int WriteTextinFile(struct Text* text, const char* fName, const char* mode)
{
    FILE* fop = fopen(fName, mode);
    if(fop == NULL)
    {
        perror("fopen()");
        errParse(FOPEN_ERROR);
    }

    fprintf(fop, "\n\n");
    for(size_t i = 0; i < text->nLines; i++)
    {
        fprintf(fop, "%s\n", text->lines[i].ptr);
    }
    fclose(fop);
    return 0;
}
