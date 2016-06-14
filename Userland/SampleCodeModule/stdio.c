#include "include/stdio.h"
#include "include/math.h"

#define STD_IN 		0
#define STD_OUT		1
#define STD_ERR 	2

// TODO: change to string library.
int
strlen( const char * str );

int
strncmp( const char * str1 , const char * str2 , int length );

int
strncmp( const char * str1 , const char * str2 , int length ){
	int i, aux;
	for ( i = 0; i < length ; i++ ){
		aux = str1[i] - str2[i];
		if ( !aux ){
			return aux;
		}
	}
	return 0;
}

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
	return size-1;
}

int
printf( const char * str, void ** args){
	int ans = 0;
	int index = 0;
	int arg = 0;
	int aux = 0;
	char * buf;
	char c;
	while ( str[index] != '\0' ){
		c = str[index++];
		if ( c != '%'){
			putchar(c);
		}else{
			ans++;
			c = str[index++];
			switch(c){
				case 's':
					puts((char *) args[arg++]);
					break;
				case 'd':
					aux = i_to_s(buf, ((int *) (args[arg++]))[0], 10);
					buf[aux] = 0;
					puts(buf);
					break;
				default:
					break;
			}
		}
	}
	return ans;
}
