#include "twamp_alloc.h"

#include <stdlib.h>

void* twamp_malloc(size_t size)
{
    return malloc(size);
}

void twamp_free(void* ptr)
{
    free(ptr);
}
