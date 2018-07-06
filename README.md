# Atkin

<br />

## Overview

**Atkin** is a C implementation of the
[Sieve of Atkin](https://en.wikipedia.org/wiki/Sieve_of_Atkin), as well as a command-line tool for
generating a list of primes up to a given limit.

## Documentation

To compile:

```bash
$ make
```

To generate the first 1,000,000 primes:

```bash
$ ./atkin 1000000
```

## API

Example program to generate the first 1,000,000 primes and print them, one per line:

```c
#include <inttypes.h>
#include <stdio.h>

#include "sieve.h"
#include "atkin.h"


#define IS_PRIME(s, n) \
    SIEVE_IS_PRIME(s, n)

#define LIMIT 1000000


int main(int argc, char* const argv[])
{
    sieve_t s;
    if (sieve_init(&s, LIMIT) < 0)
    {
        /* Error: Insufficient memory to allocate sieve. */
    }
    
    /* Build the sieve. */
    atkin_make(&s);
    
    uint64_t i = 0;
    
    /* Print all primes. */
    for ( ; i < LIMIT; ++i)
    {
        if (IS_PRIME(s, i))
        {
            printf("%" PRIu64 "\n", i);
        }
    }
    
    sieve_free(&s);
    
    return 0;
}
```

## Alternatives

* [primegen](https://cr.yp.to/primegen.html) by D. J. Bernstein
