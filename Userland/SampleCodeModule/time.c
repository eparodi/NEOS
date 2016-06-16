#include "include/stdlib.h"

typedef char ntime;

char *
get_hour(){
	ntime seconds = time(0);
	ntime minutes = time(2);
	ntime hours = time(4);
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
		i_to_s(&buff[7], minutes, 10);
	}else{
		i_to_s(&buff[6], minutes, 10);
	}

	return buff;
}