#ifndef STDLIB_H
#define STDLIB_H

#define NULL 0
/*
 * Allocate memoy
 * Parameters:
 *  -s: size.
 */
void * malloc(int s);
/*
 * Liberate memoy
 * Parameters:
 *  -addr: memorry address.
 */
void free(char* addr);

/*
 * Sleeps the pc for a period of time.
 * Parameters:
 *  -time: the amount of time to sleep, on ticks.
 */
 void
 sleep(int time);
#endif
