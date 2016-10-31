#include "stdlib.h"

#define MEM_START 0x10000000

typedef unsigned char byte;

static byte * mem= (byte *)MEM_START;


void* malloc(int s){
	void * tor= mem;
	mem+=s;
	return tor;
}

void free(char* addr){
	return;
}
