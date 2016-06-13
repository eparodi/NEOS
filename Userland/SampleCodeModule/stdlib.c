//#include "stdlib.h"

#define MEM_START 0x10000000

typedef unsigned char byte;

static byte * mem= MEM_START;


void* malloc(int s){
	int tor=mem;
	mem+=s;
	return (void*)tor;
}

void free(char* addr){
	return;
}
