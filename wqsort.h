#ifndef WQSORT_H_INCLUDED
#define WQSORT_H_INCLUDED

typedef int (compar_t)(const void*, const void*);

void swapObjects(void* a, void* b, size_t size);
void wqsort(void* ptr, size_t count, size_t size, compar_t);

#endif