#include "include/stdlib.h"
#include "include/math.h"
#include "include/time.h"

typedef unsigned char ntime;

/*
 *	Returns the interpreted data from the RTC.
 *	Paramaters:
 *		-option: the id of the data requested. (See rtc.h)
 *	Return:
 *		The time data requested or -1 if the data could not be read.
 */
int
time(int option);

/* Current time zone */
static int gmt = -3;

char *
get_hour(){
	ntime seconds = time(0);
	ntime minutes = time(2);
	ntime hours = time(4) + gmt;
	char * buff = malloc(9*sizeof(char));
	for ( int i = 0; i < 8; i++ ){
		buff[i] = '0';
	}

	buff[2]=':';
	buff[5]=':';
	buff[8]='\0';

	if ( hours < 10 ){
		i_to_s(&buff[1], hours, 10);
	}else{
		i_to_s(buff, hours, 10);
	}

	if ( minutes < 10 ){
		i_to_s(&buff[4], minutes, 10);
	}else{
		i_to_s(&buff[3], minutes, 10);
	}

	if ( seconds < 10 ){
		i_to_s(&buff[7], seconds, 10);
	}else{
		i_to_s(&buff[6], seconds, 10);
	}

	return buff;
}

char*
get_date(){
	ntime day = time(7);
	ntime month = time(8);
	ntime year = time(9);

	char * buff = malloc(9*sizeof(char));
	for ( int i = 0; i < 8; i++ ){
		buff[i] = '0';
	}

	buff[2]='/';
	buff[5]='/';
	buff[8]='\0';

	if ( month < 10 ){
		i_to_s(&buff[1], month, 10);
	}else{
		i_to_s(buff, month, 10);
	}

	if ( day < 10 ){
		i_to_s(&buff[4], day, 10);
	}else{
		i_to_s(&buff[3], day, 10);
	}

	if ( year < 10 ){
		i_to_s(&buff[7], year, 10);
	}else{
		i_to_s(&buff[6], year, 10);
	}

	return buff;
}
