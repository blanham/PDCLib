/* ----------------------------------------------------------------------------
 * $Id$
 * ----------------------------------------------------------------------------
 * Public Domain C Library - http://pdclib.sourceforge.net
 * This code is Public Domain. Use, modify, and redistribute at will.
 * --------------------------------------------------------------------------*/

void free( void * ptr ) { /* TODO */ };

/* Thomas "Beyond Infinity" Kreitner's code - unchecked, unoptimized
{
    chunk_t * chunk;
    chunk_t * prev_chunk;
    chunk = used_mem.start;
    do
    {
        prev_chunk = chunk;
        chunk = chunk->next;
    } while ( ( chunk != NULL ) && ( chunk->address != ptr ) );
    if ( chunk->address == ptr )
    {
    if( used_mem.start->next->next == NULL )
    {
        /* used_mem list has only one entry */
        chunk = used_mem.start->next;
        used_mem.last = used_mem.start;
    }
    else if ( chunk == used_mem.last )
    {
        /* chunk is the last element of used_mem list */
        prev_chunk->next = NULL;
        used_mem.last = prev_chunk;
    }
    else
    {
        /* chunk is neither only nor last in the used_mem list */
        prev_chunk->next = prev_chunk->next->next;
    }
    chunk->next = NULL;
    free_mem.last->next = chunk;
    free_mem.last = chunk;
    return chunk;
    }
    else
    {
        return NULL;
    }
}
