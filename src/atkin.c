/**
 * Copyright (c) 2018 Joshua Inscoe
 * Use of this source code is governed by the MIT License.
 *
 * atkin.c
 */



#include "atkin.h"


#include <stdint.h>


#include "sieve.h"



void atkin_make(sieve_t* s)
{
    register uint64_t x = 1;
    register uint64_t y = 1;
    register uint64_t xx_mul1 = 1 * x * x;
    register uint64_t xx_mul3 = 3 * x * x;
    register uint64_t xx_mul4 = 4 * x * x;
    register uint64_t yy_mul1 = 1 * y * y;

    register uint64_t limit = SIEVE_LIMIT(*s);

    register uint64_t n = 0;

    register uint64_t i = 5;
    register uint64_t ii_mul1 = 1 * i * i;

    while (yy_mul1 < limit)
    {
        while (xx_mul1 < limit)
        {
            if (x <= y)
            {
                goto _skip;
            }

            n = xx_mul3 - yy_mul1;
            if (n < limit)
            {
                switch (n % 12)
                {
                    case 11:
                        SIEVE_XORBIT(*s, n);
                }
            }
            else
            {
                break;
            }

_skip:
            n = xx_mul3 + yy_mul1;
            if (n < limit)
            {
                switch (n % 12)
                {
                    case 7:
                        SIEVE_XORBIT(*s, n);
                }
            }
            else
            {
                goto _next;
            }

            n = xx_mul4 + yy_mul1;
            if (n < limit)
            {
                switch (n % 12)
                {
                    case 1:
                    case 5:
                        SIEVE_XORBIT(*s, n);
                }
            }
            else
            {
                goto _next;
            }

_next:
            ++x;
            xx_mul1 = 1 * x * x;
            xx_mul3 = 3 * x * x;
            xx_mul4 = 4 * x * x;
        }

        x = 1;
        xx_mul1 = 1 * x * x;
        xx_mul3 = 3 * x * x;
        xx_mul4 = 4 * x * x;

        ++y;
        yy_mul1 = 1 * y * y;
    }

    while (ii_mul1 < limit)
    {
        if (SIEVE_GETBIT(*s, i))
        {
            n = ii_mul1;

            for ( ; n < limit; n += ii_mul1)
            {
                SIEVE_CLRBIT(*s, n);
            }
        }
#ifdef ATKIN_OPTIMIZE
        else
        {
            /*
             * This actually tends to run slower than it would without the below "optimization",
             * so it's usually best to leave ATKIN_OPTMIZE undefined.
             */
            if (((uint8_t *)s->_sieve)[(i >> 3)])
            {
                goto _next2;
            }
            else
            {
                i +=  6;
            }
            if (((uint16_t*)s->_sieve)[(i >> 4)])
            {
                goto _next2;
            }
            else
            {
                i +=  8;
            }
            if (((uint32_t*)s->_sieve)[(i >> 5)])
            {
                goto _next2;
            }
            else
            {
                i += 16;
            }
            if (((uint64_t*)s->_sieve)[(i >> 6)])
            {
                goto _next2;
            }
            else
            {
                i += 32;
            }
        }

_next2:
#endif /* ATKIN_OPTIMIZE */

        i += 2;
        ii_mul1 = i * i;
    }

    SIEVE_SETBIT(*s, 2);
    SIEVE_SETBIT(*s, 3);

    return;
}
