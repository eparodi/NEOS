#include "stdio.h"

#define STD_IN 		0
#define STD_OUT		1
#define STD_ERR 	2

// TODO: change to string library.
int
strlen( const char * str );

int
putchar( char letter ){
	write(STD_OUT, &letter,1);
	return letter;
}

int
getc(){
	char ans;
	read(STD_IN, &ans, 1);
	return ans;
}

int
puts( const char * str ){
	return write(1, str, strlen(str));
}

int
strlen( const char * str ){
	int size = 0;
	while( str[size++] != '\0' ){}
	return size;
}
