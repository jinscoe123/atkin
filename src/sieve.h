/**
 * Copyright (c) 2018 Joshua Inscoe
 * Use of this source code is governed by the MIT License.
 *
 * sieve.h
 */



#ifndef SIEVE_H
#define SIEVE_H


#include <stdint.h>



#ifdef __cplusplus
extern "C" {
#endif


struct _sieve
{
    unsigned char* _sieve;
    uint64_t _limit;
};


/*
 * A type for representing a prime number sieve.
 */
typedef struct _sieve sieve_t;



#define SIEVE_GETBIT(s, n) \
    (((s)._sieve)[((n) >> 3)] &   (1 << ((n) & 0x07)))

#define SIEVE_SETBIT(s, n) \
    ( (s)._sieve)[((n) >> 3)] |=  (1 << ((n) & 0x07) )

#define SIEVE_XORBIT(s, n) \
    ( (s)._sieve)[((n) >> 3)] ^=  (1 << ((n) & 0x07) )

#define SIEVE_CLRBIT(s, n) \
    ( (s)._sieve)[((n) >> 3)] &= ~(1 << ((n) & 0x07) )


/*
 * Get the sieve limit.
 *
 * This can be called only after first calling ``sieve_init()`` and populating the sieve the
 * sieve (e.g. by calling ``atkin_make()`` on the sieve).
 *
 *
 * RETURN:
 *
 * The limit up to which prime numbers can be calculated or retrieved.
 */
#define SIEVE_LIMIT(s) \
    ((s)._limit)

/*
 * Check if a number is prime.
 *
 * This can be called only after first calling ``sieve_init()`` and populating the sieve
 * (e.g. by calling ``atkin_make()`` on the sieve).
 *
 *
 * RETURN:
 *
 * If the given number is not prime, this macro returns 0.
 * Otherwise, a non-zero value is returned.
 *
 *
 * NOTE:
 *
 * Parameter, ``n``, must be less than the sieve limit, which was set during initialization.
 */
#define SIEVE_IS_PRIME(s, n) \
    SIEVE_GETBIT(s, n)



/*
 * Initialize the sieve.
 *
 * Allocate and initialize the internal state of the sieve.
 * Parameter, ``limit``, specifies the limit up to which primes will be calculated.
 *
 *
 * RETURN:
 *
 * On success, this function returns 0.
 * Otherwise -1 is returned and errno is set to indicate the error.
 */
int sieve_init(sieve_t* s, uint64_t limit);

/*
 * Free the sieve.
 *
 * Free the internal state of the sieve.
 *
 * This can be called only after first calling ``sieve_init()`` on the given sieve.
 */
void sieve_free(sieve_t* s);


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* SIEVE_H */
