/* _PDCLIB_allocpages( int const )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

/* This is an example implementation of _PDCLIB_allocpages() (declared in
   _PDCLIB_config.h), fit for use with POSIX kernels.
*/

#ifndef REGTEST
#include <stdint.h>
#include <stddef.h>
#include <sys/mman.h>
#include <_PDCLIB_glue.h>

void * _PDCLIB_allocpages( size_t n )
{
    void *addr = mmap(
        NULL, n * _PDCLIB_MALLOC_PAGESIZE, PROT_READ | PROT_WRITE,
        MAP_ANON | MAP_PRIVATE, -1, 0);

    if(addr != MAP_FAILED) {
        return addr;
    } else {
        return NULL;
    }
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    return TEST_RESULTS;
}

#endif
