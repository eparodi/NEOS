#ifndef KEYBOARD_H
#define KEYBOARD_H
#define BUFFER_SIZE 100
#include "types.h"

/*
 * 	Gets the RAW data from the Keyboard. If the data is not read, 
 * 	new IRQ's will not be sent.
 *	Return:
 *		The RAW data.
 */
byte
_read_keyboard();

void
update_screen(char keyCode);
void
add_to_buffer();
char
read_from_buffer();
static int ctrlPressed = -1;
static int shiftPressed = -1;
static int altPressed = -1;
static int mapSize = 90;
static char buffer[BUFFER_SIZE]={0};
static int read_index = 0;
static int write_index = 0;



#endif
