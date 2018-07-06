/**
 * Copyright (c) 2018 Joshua Inscoe
 * Use of this source code is governed by the MIT License.
 *
 * main.c
 */



#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>


#include "sieve.h"
#include "atkin.h"



#ifdef DEBUG
#define FMT_STRING_MAXLEN 32
#endif


#define IS_PRIME(s, n) \
    SIEVE_IS_PRIME(s, n)



static void _print_usage(FILE* fp, int argc, char* const argv[])
{
    fprintf(fp, "Usage: %s limit\n", argv[0]);
    fprintf(fp, "Arguments:\n");
    fprintf(fp, "    limit    the limit up to which to calculate primes\n");

    return;
}



int main(int argc, char* const argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "error: Argument \'limit\': Missing argument\n");
        _print_usage(stderr, argc, argv);
        exit(1);
    }
    if (argc > 2)
    {
        fprintf(stderr, "error: Trailing command-line argument(s)\n");
        _print_usage(stderr, argc, argv);
        exit(1);
    }

    int errv = 0;

    uint64_t limit = UINT64_MAX;
    char* endptr = NULL;

    errv = errno;
    errno = 0;

    limit = strtoul(argv[1], &endptr, 0);
    if (errno == ERANGE)
    {
        perror("error: Argument \'limit\': strtoul()");
        _print_usage(stderr, argc, argv);
        exit(1);
    }
    if (*endptr != '\0')
    {
        fprintf(stderr, "error: Argument \'limit\': Non-integral value\n");
        _print_usage(stderr, argc, argv);
        exit(1);
    }

    errno = errv;

#ifdef DEBUG
    size_t ndigits = 0;
    uint64_t n = limit;
    if (n > 0)
    {
        --n;
    }
    for ( ; n > 0; n /= 10, ++ndigits)
    {
        ;
    }

    char fmt[FMT_STRING_MAXLEN];
    errv = snprintf(fmt, sizeof(fmt), "%%%zu" PRIu64 " : %%s\n", ndigits);
    if (errv > sizeof(fmt))
    {
        fprintf(stderr, "error: snprintf(): Failed to create format string\n");
        exit(1);
    }
    if (errv < 0)
    {
        fprintf(stderr, "error: snprintf(): Failed to create format string\n");
        exit(1);
    }
#endif

    sieve_t s = { NULL, 0 };

    errv = sieve_init(&s, limit);
    if (errv < 0)
    {
        perror("error: sieve_init()");
        exit(1);
    }

    atkin_make(&s);

    uint64_t i = 0;

    for ( ; i < limit; ++i)
    {
#ifdef DEBUG
        if (IS_PRIME(s, i))
        {
            printf(fmt, i, "1");
        }
        else
        {
            printf(fmt, i, "0");
        }
#else
        if (IS_PRIME(s, i))
        {
            printf("%" PRIu64 "\n", i);
        }
#endif
    }

    sieve_free(&s);

    return 0;
}
