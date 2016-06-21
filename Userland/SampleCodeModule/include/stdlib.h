#ifndef STDLIB_H
#define STDLIB_H

#define NULL 0
/*
 * Allocate memoy
 * Parameters:
 *  -s: size.
 */
char* malloc(int s);
/*
 * Liberate memoy
 * Parameters:
 *  -addr: memorry address.
 */
void free(char* addr);

#endif