#ifndef RTC_H
#define RTC_H

#include "types.h"

//http://stanislavs.org/helppc/cmos_ram.html

//STATUS: NOT WORKING.

//DATA_ID
#define SECONDS              0x00
#define	SECONDS_ALARM        0x01
#define	MINUTES              0x02
#define MINUTES_ALARM        0x03
#define	HOURS                0x04
#define	HOURS_ALARM          0x05
#define	DAY_OF_THE_WEEK      0x06
#define	DAY_OF_THE_MONTH	 0x07
#define	MONTH                0x08
#define	YEAR                 0x09
#define SEGMENT_A			 0x0A

#define IS_UPDATING_MASK	 0x80

/*
 *	Gets the RAW data from the RTC.
 *	Parameters:
 *		-data_id: the number associated with the data wanted to be read.
 *	Return:
 *		The RAW data.
 */
word
_get_rtc_data(byte data_id);

/*
 *	Writes data in the RTC.
 *	Parameters:
 *		-data_id: the number associated with the data wanted to be read.
 *		-data: the data going to be written.
 */
void
_write_rtc_data(byte data_id, word data);

/*
 *	Receives the seconds from the RTC.
 *	Return:
 *		The seconds from the RTC.
 */
word
get_seconds();

/*
 *	Receives the minutes from the RTC.
 *	Return:
 *		The minutes from the RTC.
 */
word
get_minutes();

/*
 *	Receives the hours from the RTC.
 *	Return:
 *		The hours from the RTC.
 */
word
get_hours();

/*
 *	Checks if the time is updating.
 *	Return:
 *		True if the RTC is updating.
 */
 boolean
 is_updating();

/*
 *	Gets the interpreted data from the RTC.
 *	Parameters:
 *		-option: the number associated with the data wanted to be read.
 *	Return:
 *		The interpreted data.
 */
int
 get_time_data(int option);

#endif