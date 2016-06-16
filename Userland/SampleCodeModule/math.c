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
	char letters[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N',
						'O','P','Q','R','S','T','U','V','W','X','Y','Z'};

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
			buffer[i] = letters[aux - 10]; 
		}else{
			buffer[i] = number % radix + '0';
		}
		number /= radix;
	}
	return size;
}