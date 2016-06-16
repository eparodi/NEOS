#include "include/rtc.h"
#include "include/types.h"

word
bcd_to_normal(word data);

word
normal_to_bcd(word data);

word
getSeconds(){
	return _get_rtc_data(SECONDS);
}

word
getMinutes(){
	return bcd_to_normal(_get_rtc_data(MINUTES));
}

word
getHours(){
	return bcd_to_normal(_get_rtc_data(HOURS));	
}

boolean
is_updating(){
	word segment = _get_rtc_data(SEGMENT_A);
	segment = segment & IS_UPDATING_MASK;
	if ( segment != 0){
		return true;
	}else{
		return false;
	}
}

word
bcd_to_normal(word data){
	word aux = data;
	aux = aux & 0xFF; // get the first digit.
	data = (data >> 8) * 10;
	return aux + data;
}

word normal_to_bcd(word data){
	return (data % 10) + (data / 10) * 0xFF ;
}