/* ----------------------------------------------------------------------------
 * $Id$
 * ----------------------------------------------------------------------------
 * Public Domain C Library - http://pdclib.sourceforge.net
 * This code is Public Domain. Use, modify, and redistribute at will.
 * --------------------------------------------------------------------------*/

void * realloc( void * ptr, size_t size ) { /* TODO */ };

/* PDPC code - assumes size_t of memory chunk at offset -4.
{
    char * newptr;
    size_t oldsize;

    if ( ( newptr = malloc(size) ) != NULL )
    {
        if ( ptr != NULL )
        {
            // reading size information from hidden chunk header
            oldsize = * (size_t *) ( (char *) ptr - 4 );
            // correctly handle *down*sizing as well as *up*sizing
            memcpy( newptr, ptr, ( oldsize < size ) ? oldsize : size );
            free( ptr );
        }
    }
    return ( newptr );
}
*/

/* Thomas "Beyond Infinity" Kreitner's code - unchecked, unoptimized
{
    uint_t found = 0;
    uint_t length;
    chunk_t * new;
    chunk_t * chunk;
    // searching the block to-be-allocated
    chunk = used_mem.start;
    while ( ! found && ( chunk->next != NULL )
    {
        if ( chunk->address == ptr )
        {
            found++;
        }
        else
        {
            chunk=chunk->next;
        }
    }
    if ( found )
    {
        length = chunk->length;
        // allocate new memory area
        if ( ( new = (void *) malloc( size ) ) != NULL )
        {
            // copy the data
            memcpy( ptr, new, length );
            // release the old memory
            free( ptr );
        }
        else
        {
            new = NULL;
        }
    }
    else
    {
        new = NULL;
    }
    return new;
}
*/
