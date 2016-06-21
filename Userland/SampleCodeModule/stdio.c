#include "include/stdio.h"
#include "include/math.h"
#include <stdarg.h>

#define STD_IN 		0
#define STD_OUT		1
#define STD_ERR 	2


int
strlen( const char * str );

int
strncmp( const char * str1 , const char * str2 , int length );

int
strncmp( const char * str1 , const char * str2 , int length ){
	int i, aux;
	for ( i = 0; i < length ; i++ ){
		aux = str1[i] - str2[i];
		if ( aux ){
			return aux;
		}
	}
	return 0;
}

int strcmp(const char * str1,const char * str2){
	int i, aux;
	for ( i = 0; str1[i]!=0 || str2[i]!=0 ; i++ ){
		aux = str1[i] - str2[i];
		if ( aux ){
			return aux;
		}

	}

	return str1[i]-str2[i];
}

int
putchar( char letter ){
	write(STD_OUT, &letter,1);
	return letter;
}
static int k = 0;
int
getc(){
	char ans;
	unsigned int c =0;
	//printf("entro" );
	do{
		c = read(0, &ans, 1);
	}while(c == 0);
	//printf("salgo" );
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
printf( const char * str, ...){
	va_list args;
	int ans = 0;
	int index = 0;
	int arg = 0;
	int aux = 0;
	char buf[30];
	char c;
	va_start(args, arg);
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
				case 'c':
					putchar(va_arg(args,char));
					break;
				case 'd':
					aux = i_to_s(buf, va_arg(args, int), 10);
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

/* %c y %d no andan scan*/
int
scanf( const char * str, ...){
	va_list args;
	int ans = 0;
	int index = 0;
	int arg = 0;
	int aux = 0;
	int i ;
	int k=0;
	int ax;
	char buf[30]={0};
		char num[1000]={0};
	char c;
	va_start(args, arg);
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
					//	printf("paso" );
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
				//	printf("paso" );
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
