#ifndef TWAMP_TWAMP_ALLOC_H
#define TWAMP_TWAMP_ALLOC_H

#include <stdlib.h>

void* twamp_malloc(size_t size);
void twamp_free(void* ptr);

#endif //TWAMP_TWAMP_ALLOC_H
