#ifndef STDIO_H
#define STDIO_H

#define NULL 0

/*
 *	Writes data in the correspondent file descriptor.
 *	Paramaters:
 *		-handle: the file descriptor.
 *		-buffer: the pointer to the buffer.
 *		-length: the length of the message.
 *	Return:
 *		The write system call return value.
 */
int
write( int handle, const char * buffer, unsigned length );

/*
 *	Writes a character in the Standard Output.
 *	Return:
 *		The character written.
 */
int
putchar( char letter );

/*
 *	Reads data from the correspondent file descriptor.
 *	Paramaters:
 *		-handle: the file descriptor.
 *		-buffer: the pointer to the buffer.
 *		-length: the length of the message going to be read.
 *	Return:
 *		The write system call return value.
 */
int
read( int handle, char * buffer, unsigned length );

/*
 * 	Writes the string given in the Standard Output.
 *	Return:
 *		The write system call return value.
 */
int
puts( const char * str );

/*
 * Implementation
 * of print formatted, it is
 * here to use.
 * Parameters:
 *		-str: the string with the format.
 *		-... a list of parameters.
 * Return:
 *		The number of parameters.
 */
int
printf( const char * str, ...);

/*
 * Clears the screen.
 */
void
cls();


int
scanf( const char * str, ...);
int
getc();

#endif
