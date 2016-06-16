#ifndef TIME_H
#define TIME_H

/*
 *	Returns the interpreted data from the RTC.
 *	Paramaters:
 *		-option: the id of the data requested. (See rtc.h)
 *	Return:
 *		The time data requested.
 */
int
time(int option);

/*
 *
 */
int
get_hour();

#endif