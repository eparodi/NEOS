#include "include/stdlib.h"

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
digits(long number, int base){
	int ans = 0;
	if (number == 0)
		return 1;
	
	if ( number < 0 ){
		number *= -1;
		ans++;
	}

	while ( number != 0 ){
		number /= base;
		ans++;
	}
	return ans;
}

int
i_to_s(char * str, long number, int base){
	int size, i, aux, aux_size;
	char letters[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N',
						'O','P','Q','R','S','T','U','V','W','X','Y','Z'};

	size = digits(number, base);
	aux_size = size;

	if ( number < 0 ){
		str[0] = '-';
		number *= -1;
		str++;
		aux_size--;
	}

	for(i = aux_size - 1; i >= 0 ; i-- ){
		aux = number % base;
		if ( aux >= 10 && aux <= 37){
			str[i] = letters[aux - 10]; 
		}else{
			str[i] = number % base + '0';
		}
		number /= base;
	}
	return size;
}