/**
 * Copyright (c) 2018 Joshua Inscoe
 * Use of this source code is governed by the MIT License.
 *
 * sieve.c
 */



#include "sieve.h"


#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>



int sieve_init(sieve_t* s, uint64_t limit)
{
#if SIZE_MAX < UINT64_MAX
    if ((limit >> 3) + 1 > SIZE_MAX)
    {
        errno = EOVERFLOW;
        return -1;
    }
#endif

    size_t size = (limit >> 3) + 1;

    unsigned char* sieve = (unsigned char*)calloc(1, size);
    if (!sieve)
    {
        return -1;
    }

    s->_sieve = sieve;
    s->_limit = limit;

    return 0;
}


void sieve_free(sieve_t* s)
{
    if (s)
    {
        free(s->_sieve);
    }

    return;
}
