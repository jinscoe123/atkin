/**
 * Copyright (c) 2018 Joshua Inscoe
 * Use of this source code is governed by the MIT License.
 *
 * atkin.h
 */



#ifndef ATKIN_H
#define ATKIN_H


#include "sieve.h"



#ifdef __cplusplus
extern "C" {
#endif


/*
 * Build the sieve.
 *
 * Execute the Sieve of Atkin algorithm to populate the prime number sieve.
 *
 * This can be called only after first calling ``sieve_init()`` on the given sieve.
 */
void atkin_make(sieve_t* s);


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* ATKIN_H */
