#ifndef VSA_DRIVER_H
#define VSA_DRIVER_H

#include "types.h"

/*
 * Starts the video mode configuration. Loads the screen memory pointer in the drivers.
 */
void
start_video_mode();

/*
 * Draws a pixel in the indicated coordinates.
 * -Parameters:
 *		-x: the x coordinate.
 *		-y: the y coordinate.
 *		-color: the color in RGB.
 */
void
draw_pixel(int x, int y, int color);

/*
 * Draws a Character in the indicated coordinates.
 * -Parameters:
 *		-c: the character.
 *		-x: the x coordinate.
 *		-y: the y coordinate.
 *		-color: the color in RGB.
 */
void
draw_char(unsigned char c, int x, int y, int color);

/*
 * Draws a String in the indicated coordinates.
 * -Parameters:
 *		-str: the string.
 *		-x: the x coordinate.
 *		-y: the y coordinate.
 *		-color: the color in RGB.
 */
void
draw_string( char * str , int x , int y , int color);

/*
 * Draws a filled rectangle from two points, the lower right and the upper right.
 * NOTE: the coordinates of the first point (x1, y1) are always lower than the ones
 * of the second point.(x2, y2) If not, the rectangle will not be drawn.
 * -Parameters:
 *		-x1: the x coordinate of the first point.
 *		-y1: the y coordinate of the first point.
 *		-x2: the x coordinate of the second point.
 *		-y2: the y coordinate of the second point.
 *		-color: the color in RGB.
 */
void
draw_filled_rectangle(int x1, int y1, int x2, int y2, int color);

/*
 * Blackens the screen and resets the writing position.
 */
void
clear_screen();

/*
 * Writes a character in the next writing position.
 * -Parameters:
 *		-c: the character written.
 *		-color: the color in RGB.
 */
void
print_char(unsigned char c, int color );

/*
 * Prints a String in the next writing position.
 * -Parameters:
 *		-str: the string.
 *		-color: the color in RGB.
 */
void
print_string(const char * str, int color );

/*
 * Prints a String until the indicated length. It is used by the SystemCall
 * to print.
 * -Parameters:
 *		-str: the string.
 *		-length: the x coordinate.
 *		-color: the color in RGB.
 */
void
print_string_by_length(const char * str, int length , int color);

/*
 * Deletes the character in the previous writing position.
 */
void
delete();

void
update_buffer_position();

int
get_buffer_position();

int
get_buffer_max_per_line();

 /*
  *  Ends the line and continue drawing characters in the bottom line.
  */
 void
 nextLine();

#endif
