/* sampleCodeModule.c */
#include "include/stdio.h"
#include "include/math.h"
#include "include/stdlib.h"
#include "include/shell.h"

//static int var1 = 0;
//static int var2 = 0;

int
main() {
	//All the following code may be removed
	//	clearScreen();
	start_shell();
	//	printf("The test text is: %s", &test);
	//Test if BSS is properly set up
	//if (var1 == 0 && var2 == 0)
	//	return 0xDEADC0DE;

	return 0xDEADBEEF;
}
