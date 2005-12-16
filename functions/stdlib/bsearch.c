/* $Id$ */

/* Release $Name$ */

/* bsearch( const void *, const void *, size_t, size_t, int(*)( const void *, const void * ) )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdlib.h>

#ifndef REGTEST

void * bsearch( const void * key, const void * base, size_t nmemb, size_t size, int (*compar)( const void *, const void * ) )
{
    const void * pivot;
    int rc;
    int corr;
    while ( nmemb )
    {
        /* algorithm needs -1 correction if remaining elements are an even number. */
        corr = ( nmemb % 2 ) - 1;
        nmemb /= 2;
        pivot = (const char *)base + (nmemb * size);
        rc = compar( key, pivot );
        if ( rc > 0 )
        {
            base = (const char *)pivot + size;
            nmemb += corr;
        }
        else if ( rc == 0 )
        {
            return (void *)pivot;
        }
    }
    return NULL;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int compare( const void * left, const void * right )
{
    return *( (unsigned char *)left ) - *( (unsigned char *)right );
}

int main()
{
    BEGIN_TESTS;
    TESTCASE( bsearch( "e", abcde, 4, 1, compare ) == NULL );
    TESTCASE( bsearch( "e", abcde, 5, 1, compare ) == &abcde[4] );
    TESTCASE( bsearch( "a", abcde + 1, 4, 1, compare ) == NULL );
    TESTCASE( bsearch( "0", abcde, 1, 1, compare ) == NULL );
    TESTCASE( bsearch( "a", abcde, 1, 1, compare ) == &abcde[0] );
    TESTCASE( bsearch( "a", abcde, 0, 1, compare ) == NULL );
    TESTCASE( bsearch( "e", abcde, 3, 2, compare ) == &abcde[4] );
    TESTCASE( bsearch( "b", abcde, 3, 2, compare ) == NULL );
    return TEST_RESULTS;
}

#endif
