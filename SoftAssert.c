#include <stdarg.h>
#include <io.h>
#include <stdio.h>
#include "SoftAssert.h"


int colorVprintf (FILE* stream, const char* format, enum spectrum color, va_list ap);
int vibrantPrint(enum spectrum color, FILE* output_stream, const char* str, ...);


void cAssert(const char* condition_s, const char* file, const char* func, int line, \
            const char* comment, ...)
{
    va_list factor;
    va_start(factor, comment);

    colorVprintf(stderr, comment, red, factor);
    vibrantPrint(red, stderr, "Assertion failed: %s. %s -> %s -> %d",
                 condition_s, file, func, line);

    va_end (factor);
    abort();
} 

void whisper(const char* file, const char* func, int line, \
             const char* comment, ...)
{
    va_list factor;
    va_start(factor, comment);

    colorVprintf(stderr, comment, red, factor);
    vibrantPrint(red, stderr, "Assertion failed: %s. %s -> -> %d",
                 file, func, line);

    va_end (factor);
} 



int colorVprintf (FILE* stream, const char* format, enum spectrum color, va_list ap)
{
    if (_isatty(_fileno(stream)))
    {
        const char* const VP_COLORS_AR[] = {"\033[1;31m", "\033[32m", "\033[0m"};

        fprintf(stream, "%s", VP_COLORS_AR[color]);

        int c_read = vfprintf(stream, format, ap);

        fprintf(stream, "%s", "\033[0m");

        return c_read;
    }
    else
    {
        return vfprintf(stream, format, ap);
    }

}


enum spectrum
{
    red   ,
    green ,
    blue  ,
    yellow,
    orange,
    reset
};




//---------------------------------------------------------------------------
//! Output function based on frprintf(). Can redirect stream to selected file
//! with selected color.
//!
//! @param [in] color Color name (currently supports all colors of rainbow)
//!
//! @param [in] output_stream FILE pointer.
//!
//! @param [in] str String to print
//!
//! @param [in] identificators Works exactly like printf() from stdio.h library.
//------------------------------------------------------------------------------

int vibrantPrint(enum spectrum color, FILE* output_stream, const char* str, ...)
{
    va_list factor;
    va_start(factor, str);

    if (_isatty(_fileno(output_stream)))
    {
        int c_read = color_vprintf(output_stream, str,  color, factor);

        va_end(factor);

        return c_read;
    }

    else
    {
        va_end(factor);
        return vfprintf(output_stream, str, factor);
    }
}