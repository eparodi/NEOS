#include "include/stdlib.h"
#include "math.h"

long
pow(long base, long exponent){
	long ans = 1;
	long i;
	for ( i = 1 ; i <= exponent ; i++ ){
		ans *= base;
	}

	return ans;
}


int
digits(long number, int radix){
	int ans = 0;
	if (number == 0)
		return 1;

	if ( number < 0 ){
		number *= -1;
		ans++;
	}

	while ( number != 0 ){
		number /= radix;
		ans++;
	}
	return ans;
}

int
i_to_s(char * buffer, long number, int radix){
	int size, i, aux, aux_size;


	size = digits(number, radix);
	aux_size = size;

	if ( number < 0 ){
		buffer[0] = '-';
		number *= -1;
		buffer++;
		aux_size--;
	}

	for(i = aux_size - 1; i >= 0 ; i-- ){
		aux = number % radix;
		if ( aux >= 10 && aux <= 37){
			buffer[i] = 'A'+(aux - 10);
		}else{
			buffer[i] = number % radix + '0';
		}
		number /= radix;
	}
	return size;
}

int
s_to_i(char* buffer){

	int i,number=0;
	int posNum = 1;
	if ( buffer[0]== '-'  ){
		posNum = -1;
		buffer++;
	}
	i=0;

	int factor ;
	int size = 0;
	while(buffer[i] != '\0'){
		i++;
		size++;
	}
	factor = size -1;
	i=0;

	while(buffer[i] != '\0'){
		number+= pow(10,factor--)*(buffer[i]-'0');
		i++;
	}
	return number*posNum;
}

int
char_hexa_to_i(char c){
	if ( c >= '0' && c <= '9' ){
		return c - '0';
	}else if ( c >= 'A' || c <= 'F'){
		return 10 + c - 'A';
	}else if ( c >= 'a' || c <= 'f') {
		return 10 + c - 'a';
	}else{
		return -1;
	}
}
