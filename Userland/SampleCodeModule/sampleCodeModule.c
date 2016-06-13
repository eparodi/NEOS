/* sampleCodeModule.c */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;

int
main() {
	//All the following code may be removed 
	char * test = "test text";
	printf("The test text is: %s", &test);
	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}
