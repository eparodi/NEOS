#include <debug.h>

int
digits(long number, int radix);

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
parse_int(char * buffer, long number, int radix){
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
