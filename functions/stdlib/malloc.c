/* ----------------------------------------------------------------------------
 * $Id$
 * ----------------------------------------------------------------------------
 * Public Domain C Library - http://pdclib.sourceforge.net
 * This code is Public Domain. Use, modify, and redistribute at will.
 * --------------------------------------------------------------------------*/

#include <__size_t.h>

void * malloc( size_t size ) { /* TODO */ };

/* This is a simple best-fit / first-fit implementation heavily based on
 * Thomas "Beyond Infinity" Kreitner's code
 */

/* memory list element */
struct chunk_t
{
    void *    address;
    size_t    size;
    chunk_t * next;
};

struct memlist_t
{
    chunk_t * start;
    chunk_t * last;
};

size_t heap_start = 0xa0000000;
size_t heap_used  = 0x00000050; /* HEAP in use. Holds the next FREE address (?) */
size_t heap_max   = 0xfffffff;  /* max. HEAP */

static struct memlist_t free_mem = { (struct memlist_t *) heap_start,
                                     (struct memlist_t *) heap_start };
/* free_mem.start->next = NULL; */

static struct memlist_t used_mem = { (struct memlist_t *) heap_start + sizeof( chunk_t ),
                                     (struct memlist_t *) heap_start + sizeof( chunk_t ) };
/* used_mem.start->next = NULL; */

void * malloc( size_t size )
{
    chunk_t * chunk = 0;
    chunk_t * prev_chunk;
    if ( free_mem.start != free_mem.last )
    {
        /* first pass: exact fit */
        chunk = free_mem.start;
        while ( 1 )
        {
            prev_chunk = chunk;
            chunk = chunk->next;
            if ( ( chunk == NULL ) || ( chunk->size == size ) )
            {
                break;
            }
        }
    }
    if ( chunk == NULL )
    {
        /* second pass - first fit */
        chunk = free_mem.start;
        while ( 1 )
        {
            prev_chunk = chunk;
            chunk = chunk-> next;
            if ( ( chunk == NULL ) || ( chunk->size > size ) )
            {
                break;
            }
        }
    }
    if ( chunk != NULL )
    {
        /* remove chunk from free_mem list */
        if ( free_mem.start->next->next == NULL )
        {
            /* free_mem list has only one entry */
            free_mem.last = free_mem.start;
        }
        else if ( chunk == free_mem.last )
        {
            /* chunk is last element of free_mem list */
            prev_chunk->next = NULL;
            free_mem.last = prev_chunk;
        }
        else
        {
            /* chunk is neither only nor last in free_mem list */
            prev_chunk->next = prev_chunk->next->next;
        }
        /* append chunk to used_mem list */
        chunk->next = NULL;
        used_mem.last->next = chunk;
        used_mem.last = chunk;
    }
    /* append new chunk to end of used_mem list (if there's space) */
    if ( chunk == NULL )
    {
        if ( ( heap_used + size ) <= heap_max )
        {
            /* building the header */
            chunk = (chunk_t *) heap_start + heap_used + 1;
            chunk->size    = size;
            chunk->next    = NULL;
            chunk->address = chunk + sizeof( chunk_t );
            /* push heap_used past allocated area */
            heap_used += sizeof( chunk_t ) + size;
            used_mem.last->next = chunk;
            used_mem.last = chunk;
        }
        else
        {
            /* allocation would exceed max. heap size -
            /* demand more memory from kernel - not implemented */
            return 0;
        }
    }
    return (void *) chunk->address;
}
