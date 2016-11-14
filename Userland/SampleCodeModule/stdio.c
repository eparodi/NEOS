#include "include/stdio.h"
#include "include/math.h"
#include <stdarg.h>
#include "stdio.h"
#include "include/string.h"

#define STD_IN 		0
#define STD_OUT		1
#define STD_ERR 	2


int
putchar( char letter ){
	write(STD_OUT, &letter,1);
	return letter;
}

int
getc(){
	char ans;
	unsigned int c =0;
	do{
		c = read(0, &ans, 1);
	}while(c == 0);
	return ans;
}

int
puts( const char * str ){
	return write(1, str, strlen(str));
}

int
printf( const char * str, ...){
	va_list args;
	int ans = 0;
	int index = 0;
	int aux = 0;
	char buf[30];
	char c;
	va_start(args, str);
	while ( str[index] != '\0' ){
		c = str[index++];
		if ( c != '%'){
			putchar(c);
		}else{
			ans++;
			c = str[index++];
			switch(c){
				case 's':
					puts(va_arg(args, char * ));
					break;
				case 'd':
					aux = i_to_s(buf, va_arg(args, int), 10);
					buf[aux] = 0;
					puts(buf);
					break;
				case 'x':
					aux = i_to_s(buf, va_arg(args, int), 16);
					buf[aux] = 0;
					puts(buf);
					break;
				default:
					break;
			}
		}
	}
	va_end(args);
	return ans;
}

int
scanf( const char * str, ...){
	va_list args;
	int ans = 0;
	int index = 0;
	int i ;
	int k=0;
	char num[1000]={0};
	char c;
	va_start(args, str);
	while ( str[index] != 0){

		c = str[index++];
		if ( c != '%'){
		printf("Formato invalido");
		}else{
			ans++;
			c = str[index++];
			switch(c){
				case 's':
					i=0;
					char * v = va_arg(args, char * );
					do{
						k=getc();
						if(k!='\n'){
							v[i++]=k;
						}else{
							v[i++]=0;
						}
				}while(k!= '\n');
					break;
				case 'd':
				i=0;
				do{
					k=getc();
					if(k!='\n'){
						num[i++]=k;
					}else{
						num[i++]=0;
					}
			}while(k!= '\n');
			int * numb =va_arg(args,int*);

			numb[0]=s_to_i(num);

					break;
				default:
					break;
			}
		}
	}

	va_end(args);
	return ans;
}
