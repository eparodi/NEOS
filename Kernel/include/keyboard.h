#ifndef KEYBOARD_H
#define KEYBOARD_H
#define BUFFER_SIZE 1000
#include "types.h"

//TODO: add comments.

/*
 * 	Gets the RAW data from the Keyboard. If the data is not read,
 * 	new IRQ's will not be sent.
 *	Return:
 *		The RAW data.
 */
byte
_read_keyboard();

void
update_screen(unsigned char keyCode);
void
add_to_buffer();
int
read_from_buffer(int,char *);
int
numberBoard(unsigned char);
void
update_cursor();
void
erase_cursor();
void
restart_line();
#endif
