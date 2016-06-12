//#include "stdlib.h"


void* malloc(int s){
	static int actual=0x10000000;
	int tor=actual;
	actual+=s;
	return (void*)tor;
}

void free(char* addr){
	return;
}
