#ifndef VSA_DRIVER_H
#define VSA_DRIVER_H

#include "types.h"
/*
 * Starts the video mode configuration. Loads the screen memory pointer in the drivers.
 */
void
start_video_mode();

/*
 * Draw a pixel in the indicated coordinates.
 * -Parameters:
 *		-x: the x coordinate.
 *		-y: the y coordinate.
 *		-color: the color in RGB.
 */
void
draw_pixel(int x, int y, int color);

/*
 * Draw a Character in the indicated coordinates.
 * -Parameters:
 *		-c: the character.
 *		-x: the x coordinate.
 *		-y: the y coordinate.
 *		-color: the color in RGB.
 */
void
draw_char(unsigned char c, int x, int y, int color);

/*
 * Draw a String in the indicated coordinates.
 * -Parameters:
 *		-str: the string.
 *		-x: the x coordinate.
 *		-y: the y coordinate.
 *		-color: the color in RGB.
 */
void
draw_string( char * str , int x , int y , int color);

void
print_string_by_length(char * str, int length , int color);

#endif