#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "types.h"

/*
 * 	Gets the RAW data from the Keyboard. If the data is not read, 
 * 	new IRQ's will not be sent.
 *	Return:
 *		The RAW data.
 */
byte
_read_keyboard();

#endif