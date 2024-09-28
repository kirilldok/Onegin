#ifndef SOFT_ASSERT_INCLUDED
#define SOFT_ASSERT_INLCUDED

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

//#include "vibrantPrint.h"
void cAssert(const char* condition_s, const char* file, const char* func, int line, \
                 const char* comment, ...);
void whisper(const char* file, const char* func, int line, \
                 const char* comment, ...);




#ifdef NDEBUG
#define whisper
#else
#define whisper(comment, ...) whisper(__FILE__, __func__, \
                                      __LINE__, comment, ##__VA_ARGS__)
#endif

#ifdef NDEBUG
#define cAssert
#else
#define cAssert(condition, comment, ...) if(condition) \
{ cAssert(#condition, __FILE__, __func__, \
          __LINE__, comment, ##__VA_ARGS__); \
} else 
#endif

#endif



