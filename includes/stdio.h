/* ----------------------------------------------------------------------------
 * $Id$
 * ----------------------------------------------------------------------------
 * Public Domain C Library - http://pdclib.sourceforge.net
 * This code is Public Domain. Use, modify, and redistribute at will.
 * ----------------------------------------------------------------------------
 * Input/output
 * --------------------------------------------------------------------------*/

#ifndef _STDIO_H
#define _STDIO_H _STDIO_H

#ifndef _NULL
#include "__intern.h"
#endif /* _NULL */

/* ----------------------------------------------------------------------------
 * MACROS
 * --------------------------------------------------------------------------*/

#define NULL _NULL

#define _IOFBF    0   // @see setvbuf()
#define _IOLBF    1   // @see setvbuf()
#define _IONBF    2   // @see setvbuf()

#define SEEK_SET  0   // @see fseek()
#define SEEK_CUR  1   // @see fseek()
#define SEEK_END  2   // @see fseek()

#define EOF      -1

/* ----------------------------------------------------------------------------
 * TYPEDEFS
 * --------------------------------------------------------------------------*/

#ifndef _SIZE_T
#define _SIZE_T _SIZE_T
typedef __size_t size_t
#endif /* _SIZE_T */

/* file position, buffer pointer, ErrorIndicator, EOFIndicator, HostRC */
typedef FILE; /* TODO */

/* file position */
typedef fpos_t; /* TODO */

extern FILE * stdin;
extern FILE * stdout;
extern FILE * stderr;

/* ----------------------------------------------------------------------------
 * FUNCTIONS
 * --------------------------------------------------------------------------*/

/* TABLE OF CONTENTS (in order of appearance)
 *
 * General File Handling
 * * fopen()
 * * freopen()
 * * fflush()
 * * feof()
 * * ferror()
 * * clearerr()
 * * fclose()
 *
 * Rename / Remove
 * * rename()
 * * remove()
 *
 * Temporary Files
 * * tmpfile()
 * * tmpnam()
 *
 * File Positioning
 * * fseek()
 * * rewind()
 * * ftell()
 * * fgetpos()
 * * fsetpos()
 *
 * Reading
 * * fgetc()
 * * getc()
 * * getchar()
 * * ungetc()
 * * fgets()
 * * gets()
 *
 * Writing
 * * fputc()
 * * putc()
 * * putchar()
 * * fputs()
 * * puts()
 *
 * Formatted Reading
 * * fscanf()
 * * scanf()
 * * sscanf()
 * * vfscanf()
 * * vscanf()
 * * vsscanf()
 *
 * Formatted Writing
 * * fprintf()
 * * printf()
 * * sprintf()
 * * snprintf()
 * * vfprintf()
 * * vprintf()
 * * vsprintf()
 * * vsnprintf()
 *
 * Special
 * * perror()
 *
 * Binary Read / Write
 * * fread()
 * * fwrite()
 *
 * Buffer Handling
 * * setvbuf()
 * * setbuf()
 *
 */

/** File OPEN. Opens a file.
 *  @param filename Name of the file.
 *  @param mode One of r, w, a, rb, wb, ab, r+, w+, a+, rb+, wb+, ab+,
 *         specifying which mode to open the file in.
 *  @return A file handle associated with the opened file, NULL if failed.
 */
FILE * fopen( const char * restrict filename, const char * restrict mode );

/** File REOPEN. Opens the file specified by the given name, associating it
 *  with the given file handle. If filename is NULL, it is attempted to change
 *  the mode of the already opened file associated with the given file handle.
 *  (This function can e.g. be used to reassociate stdin / stdout / stderr with
 *  a filename.)
 *  @param filename Name of the file to be opened.
 *  @param mode One of r, w, a, rb, wb, ab, r+, w+, a+, rb+, wb+, ab+,
 *         specifying which mode to open the file in.
 *  @param fh The file handle to associate with the opened file.
 *  @return fh if successful, NULL if failed.
 */
FILE * freopen( const char * restrict filename, const char * restrict mode, FILE * fh );

/** File FLUSH. Flushes any output buffers of a file. If parameter is NULL,
 *  flushes output buffers for all file handles. The function is undefined for
 *  input streams or update streams when the last operation was input.
 *  @param fh The file handle.
 *  @return 0 if successful, EOF on write error (setting error indicator).
 */
int fflush( FILE * fh );

/** File EOF. Tests whether EOF is set for a given file.
 *  @param fh The file handle.
 *  @return 0 if EOF is not set, non-zero if EOF is set.
 */
int feof( FILE * fh );

/** File ERROR. Tests whether error indicator is set for a given file.
 *  @param fh The file handle.
 *  @return 0 if error indicator is not set, non-zero if set.
 */
int ferror( FILE * fh );

/** CLEAR ERRor. Clears EOF and error indicator of a FILE handle.
 *  @param fh The file handle.
 */
void clearerr( FILE * fh );

/** File CLOSE. Flushes any output buffers, closes the file, frees internal
 *  buffers, and discards the file handle.
 *  @param fh The file handle.
 *  @return 0 if successful, non-zero if failed. (In any case, the file handle
 *          is invalid afterwards.)
 */
int fclose( FILE * fh );

/* ------------------------------------------------------------------------- */

/** RENAME file. Causes a file to be no longer accessible under a given name,
 *  but a new name instead.
 *  @param filename Name of the file.
 *  @param newname New file name.
 *  @return 0 if successful, non-zero if failed. (This implementation: INT_MAX
 *          if newname already exists; INT_MIN if filename could not be found;
 *          EOF if filename is a currently open file.)
 */
int rename( const char * filename, const char * newname );

/** REMOVE file. Causes a file to be no longer accessible under a given name.
 *  @param filename Name of the file.
 *  @return 0 if successful, non-zero if failed. (This implementation: INT_MAX
 *          if the file is currently open.)
 */
int remove( const char * filename );

/* ------------------------------------------------------------------------- */

/** TeMPorary FILE. Opens a previously non-existend file in "wb+" mode that
 *  will be automatically deleted when closed, or when the program terminates.
 *  (This implementation: If program terminates abnormally, file is not
 *  deleted.)
 *  @return A file handle for the temporary file. (NULL if opening failed.)
 */
FILE * tmpfile( void )

/** TeMPorary NAMe. Generates a file name that does not yet exist in the file
 *  system, and is different from the last call to the function. Note that a
 *  file generated with this name is not "temporary", and must be remove()d
 *  normally.
 *  @param filename NULL, or a char[ L_tmpnam ] array. (Beware, calling this
 *         function with a NULL parameter is not thread-safe.)
 *  @return If 'filename' is NULL, a pointer to an internal static buffer
 *          holding the generated name. If 'filename' is not null, the
 *          generated name is stored in 'filename', and 'filename' is returned.
 *          If the filename generation fails, function returns NULL.
 */
char * tmpnam( char * filename );

/* ------------------------------------------------------------------------- */

/** File SEEK. Sets the current position in a file to the values specified by
 *  start and offset.
 *  @param fh The file handle.
 *  @param offset The offset from 'start' to position to.
 *  @param start The starting point from which to calculate the offset. May be
 *         one of SEEK_SET, SEEK_CUR, SEEK_END.
 *  @return 0 if successful, non-zero if error encountered.
 */
int fseek( FILE * fh, long offset, int start );

/** REWIND file. Equivalent to (void) fseek( fh, 0, SEEK_SET ).
 *  @param fh The file handle.
 */
void rewind( FILE * fh );

/** File TELL position. Tells the current offset into a given file.
 *  @param fh The file handle.
 *  @return The offset into the file.
 */
long ftell( FILE * fh );

/** File GET POSition. Stores the current state and position in a file.
 *  @param fh The file handle.
 *  @param pos The object to store the current state in.
 *  @return 0 if successful, non-zero if error encountered.
 */
int fgetpos( FILE * restrict fh, fpos_t * restrict pos );

/** File SET POSition. Sets the current file position to the value stored in a
 *  given fpos_t object.
 *  @param fh The file handle.
 *  @param pos The fpos_t object.
 *  @return 0 if successful, non-zero if error encountered.
 */
int fsetpos( FILE * fh, const fpos_t * pos );

/* ------------------------------------------------------------------------- */

/** File GET Character. Reads a character from file.
 *  @param fh The file handle.
 *  @return The next character in the file, as unsigned char converted to int,
 *          or EOF if end of file is reached.
 */
int fgetc( FILE * fh );

/** GET Character. Equivalent to fgetc(), but may be implemented as macro, and
 *  is allowed to evaluate its parameter more than once.
 *  @param fh The file handle.
 *  @return The character read, or EOF if end of file / error encountered.
 */
int getc( FILE * fh );

/** GET CHARacter. Equivalent to getc( stdin ).
 *  @return The character read, or EOF if end of file / error encountered.
 */
int getchar( void );

/** UN-GET Character. Puts a character back into an input stream.
 *  @param c The character to put back.
 *  @param fh The file handle.
 *  @return The character put back, EOF if error encountered.
 */
int ungetc( int c, FILE * fh );

/** File GET String. Reads a line (terminated by newline character) from file,
 *  but reading no more than n characters.
 *  @param dest The char array to write into.
 *  @param n The maximum number of characters to read.
 *  @param fh The file handle.
 *  @return 'dest', or NULL if an error occurred.
 */
char * fgets( char * restrict dest, int n, FILE * restrict fh );

/** GET String. Equivalent to fgets( dest, stdin ).
 *  @param dest The character array to write to.
 *  @return 'dest', or NULL if an error occurred.
 */
char * gets( char * dest );

/* ------------------------------------------------------------------------- */

/** File PUT Character. Writes a character to file.
 *  @param c The character (when converted to unsigned char) to write.
 *  @param fh The file handle.
 *  @return 'c', or EOF if an error occurred.
 */
int fputc( int c, FILE * fh );

/** PUT Character. Equivalent to fputc( c, stdout ), but may be implemented as
 *  a macro, and may evaluate the file handle more than once.
 *  @param c The character to write.
 *  @param fh The file handle.
 *  @return The character written, or EOF if error encountered.
 */
int putc( int c, FILE * fh );

/** PUT CHARacter. Equivalent to putc( c, stdout ).
 *  @param c The character to write.
 *  @return The character written, or EOF if error encountered.
 */
int putchar( int c );

/** File PUT String. Writes a C string to file.
 *  @param src The string to write.
 *  @param fh The file handle.
 *  @return >= 0 if successful, or EOF if an error occurred.
 */
int fputs( const char * restrict src, FILE * restrict fh );

/** PUT String. Write a C string to stdout.
 *  @param src The C string to write.
 *  @return >= 0 if successful, EOF if error encountered.
 */
int puts( const char * src );

/* ------------------------------------------------------------------------- */

/** File SCAN Formatted. Reads from given file handle, under control of a
 *  formatting string, the values of variables pointed to by 0..n pointers.
 *  @param fh The file handle.
 *  @param format The formatting string.
 *  @param ... A list of 0..n pointers corresponding to placeholders in
 *         'format'.
 *  @return EOF if failed, number of values successfully assigned otherwise.
 */
int fscanf( FILE * restrict fh, const char * restrict format, ... );

/** SCAN Formatted. Equivalent to fscanf( stdin, format, ... )
 *  @param format The formatting string.
 *  @param ... A list of 0..n pointers corresponding to placeholders in
 *         'format'.
 *  @return EOF if failed, number of values successfully assigned otherwise.
 */
int scanf( const char * restrict format, ... );

/** String SCAN Formatted. Equivalent to scanf( format, ... ), but using a C
 *  string instead of a file handle for input.
 *  @param src The input string.
 *  @param format The formatting string.
 *  @param ... A list of 0..n pointers corresponding to placeholders in
 *         'format'.
 *  @return EOF if failed, number of values successfully assigned otherwise.
 */
int sscanf( const char * restrict src, const char * restrict format, ... );

/** Variable File SCAN Formatted. Equivalent to fscanf( fh, format, ... ),
 *  with the variable-length parameter list replaced by a va_list, created by
 *  the va_start macro.
 *  @param fh The file handle.
 *  @param format The formatting string.
 *  @param args The argument list created by the va_start macro.
 *  @return Number of characters printed.
 */
int vfscanf( FILE * restrict fh, const char * restrict format, va_list args );

/** Variable SCAN Formatted. Equivalent to vfscanf( stdin, format, args ).
 *  @param format The formatting string.
 *  @param args The argument list created by the va_start macro.
 *  @return Number of characters printed.
 */
int vscanf( const char * restrict format, va_list args );

/** Variable String SCAN Formatted. Equivalent to vscanf( format, args ), but
 *  reading from a C string instead of stdin.
 *  @param src The C string to read from.
 *  @param format The formatting string.
 *  @param args The argument list created by the va_start macro.
 *  @return Number of characters printed.
 */
int vsscanf( const char * restrict src, const char * restrict format, va_list ap );

/* ------------------------------------------------------------------------- */

/** File PRINT Formatted. Prints to given file handle, under control of a
 *  formatting string, the values of 0..n variables.
 *  @param fh The file handle.
 *  @param format The formatting string.
 *  @param ... A list of 0..n variables corresponding to placeholders in
 *         'format'.
 *  @return Number of characters printed, negative value if error occurred.
 */
int fprintf( FILE * restrict fh, const char * restrict format, ... );

/** PRINT Formatted. Equivalent to fprintf( stdout, format, ... ).
 *  @param format The formatting string.
 *  @param ... A list of 0..n variables corresponding to placeholders in
 *         'format'.
 *  @return Number of characters printed.
 */
int printf( const char * restrict format, ... );

/** String PRINT Formatted. Equivalent to printf( format, ... ), but writing
 *  to a char array instead of stdout.
 *  @param dest The char array to write to.
 *  @param format The formatting string.
 *  @param ... A list of 0..n variables corresponding to placeholders in
 *         'format'.
 *  @return Number of characters printed.
 */
int sprintf( char * restrict dest, const char * restrict format, ... );

/** String N PRINT Formatted. Equivalent to sprintf( dest, format, ... ), but
 *  will not write more than n characters.
 *  @param dest The char array to write to.
 *  @param n The maximum number of characters to write.
 *  @param format The formatting string.
 *  @param ... A list of 0..n variables corresponding to placeholders in
 *         'format'.
 *  @return Number of characters printed.
 */
int snprintf( char * restrict s, size_t n, const char * restrict format, ... );

/** Variable File PRINT Formatted. Equivalent to fprintf( fh, format, ... ),
 *  with the variable-length parameter list replaced by a va_list, created by
 *  the va_start macro.
 *  @param fh The file handle.
 *  @param format The formatting string.
 *  @param args The argument list created by the va_start macro.
 *  @return Number of characters printed.
 */
int vfprintf( FILE * restrict fh, const char * restrict format, va_list args );

/** Variable PRINT Formatted. Equivalent to vfprintf( stdout, format, args ).
 *  @param format The formatting string.
 *  @param args The argument list created by the va_start macro.
 *  @return Number of characters printed.
 */
int vprintf( const char * restrict format, va_list args );

/** Variable String PRINT Formatted. Equivalent to vprintf( format, args ), but
 *  writing to a char array instead to stdout.
 *  @param dest The char array to write to.
 *  @param format The formatting string.
 *  @param args The argument list created by the va_start macro.
 *  @return Number of characters printed.
 */
int vsprintf( char * restrict s, const char * restrict format, va_list ap);

/** Variable String N PRINT Formatted. Equivalent to vsprintf( dest, format,
 *  args ), but will not write more than n characters.
 *  @param dest The char array to write to.
 *  @param n Maximum number of characters to write.
 *  @param format The formatting string.
 *  @param args The argument list created by the va_start macro.
 *  @return Number of characters printed.
 */
int vsnprintf( char * restrict dest, size_t n, const char * restrict format, va_list ap );

/* ------------------------------------------------------------------------- */

/** Print ERROR.
 *  Equivalent to fprintf( stderr, "%s: %s\n", text, strerror( errno ) ).
 *  @param test Text to prepend the error message with.
 */
void perror( const char * text );

/* ------------------------------------------------------------------------- */

/** File READ. Reads a number of objects of a given size from file, and into
 *  a memory area.
 *  @param dest The memory area to write into.
 *  @param size The size of one object.
 *  @param n The number of objects to read.
 *  @param fh The file handle.
 *  @return The number of objects successfully read.
 */
size_t fread( void * restrict dest, size_t size, size_t n, FILE * restrict fh );

/** File WRITE. Writes a number of objects from a memory area to file.
 *  @param src The memory area to write from.
 *  @param size The size of a single object.
 *  @param n The number of objects to write.
 *  @param fh The file handle.
 *  @return The number of objects successfully written.
 */
size_t fwrite( const void * restrict src, size_t size, size_t n, FILE * restrict fh );

/* ------------------------------------------------------------------------- */

/** SET Virtual BUFfer. Sets buffering mode and (optionally) the memory used
 *  for buffering, for a given file handle.
 *  This function must only be called immediately after associating the file
 *  handle with a file, before any operations are called on the file handle.
 *  @param fh The file handle.
 *  @param buf A pointer to the memory area to use for buffering, or NULL to
 *         use internally assigned buffer memory.
 *  @param mode One of _IOFBF, _IOLBF, _IONBF.
 *  @param size Size of the memory area to be used for buffering.
 */
int setvbuf( FILE * restrict fh, char * restrict buf, int mode, size_t size );

/** SET BUFfer. Equivalent to (void) setvbuf( fh, buf, _IOFBF, BUFSIZ ), or
 *  (void) setvbuf( fh, NULL, _IONBF, BUFSIZ ) if buf == NULL.
 *  @param fh The file handle to be passed to setvbuf().
 *  @param buf The buffer pointer to be passed to setvbuf().
 */
void setbuf( FILE * restrict fh, char * restrict buf );

/* ------------------------------------------------------------------------- */

/* PDPC code - unreviewed
/*
    What we have is an internal buffer, which is 8 characters
    longer than the actually used buffer.  E.g. say BUFSIZ is
    512 bytes, then we actually allocate 520 bytes.  The first
    2 characters will be junk, the next 2 characters set to NUL,
    for protection against some backward-compares.  The fourth-last
    character is set to '\n', to protect against overscan.  The
    last 3 characters will be junk, to protect against memory
    violation.  intBuffer is the internal buffer, but everyone refers
    to fbuf, which is actually set to the &intBuffer[4].  Also,
    szfbuf is the size of the "visible" buffer, not the internal
    buffer.  The reason for the 2 junk characters at the beginning
    is to align the buffer on a 4-byte boundary.
*/

typedef struct
{
#if (defined(__OS2__) || defined(__32BIT__))
    unsigned long hfile;  /* OS/2 file handle */
#endif
#if (defined(__MSDOS__) || defined(__DOS__) || defined(__POWERC))
    int hfile; /* dos file handle */
#endif
#if (defined(__MVS__))
    void *hfile;
    int recfm;
    int style;
    int lrecl;
    char ddname[9];
#endif
    int quickBin;  /* 1 = do DosRead NOW!!!! */
    int quickText; /* 1 = quick text mode */
    int textMode; /* 1 = text mode, 0 = binary mode */
    int intFno;   /* internal file number */
    unsigned long bufStartR; /* buffer start represents, e.g. if we
        have read in 3 buffers, each of 512 bytes, and we are
        currently reading from the 3rd buffer, then the first
        character in the buffer would be 1024, so that is what is
        put in bufStartR. */
    char *fbuf;     /* file buffer - this is what all the routines
                       look at. */
    size_t szfbuf;  /* size of file buffer (the one that the routines
                       see, and the user allocates, and what is actually
                       read in from disk) */
    char *upto;     /* what character is next to read from buffer */
    char *endbuf;   /* pointer PAST last character in buffer, ie it
                       points to the '\n' in the internal buffer */
    int errorInd;   /* whether an error has occurred on this file */
    int eofInd;     /* whether EOF has been reached on this file */
    int ungetCh;    /* character pushed back, -1 if none */
    int bufTech;    /* buffering technique, _IOFBF etc */
    char *intBuffer; /* internal buffer */
    int noNl;       /* When doing gets, we don't copy NL */
    int mode;       /* __WRITE_MODE or __READ_MODE */
    int update;     /* Is file update (read + write)? */
    int theirBuffer; /* Is the buffer supplied by them? */
} FILE;

#endif /* _STDIO_H */
