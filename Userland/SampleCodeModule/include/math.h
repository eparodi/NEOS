#ifndef MATH_H
#define MATH_H

/*
 * An exponentiation function.
 * -Parameters:
 *		-base: the base of the power.
 *		-exponent: the exponent of the power.
 */
long
pow(long base, long exponent);

/*
 * Returns the number of digits of a number with the specified radix.
 * -Parameters:
 *		-number: the number in any radix.
 *		-radix: the radix or base.
 */
int
digits(long number, int radix);

/*
 * Writes in the conventional writing human symbols system, a number in the buffer
 * given with the specified radix.
 * NOTE: It only works if the human interpretable list of symbols implemented in
 * my system supports the conventional number symbols!
 * -Parameters:
 *		-buffer: the buffer where to write.
 *		-number: the number to print.
 *		-radix: the radix or base.
 */
int
i_to_s(char * buffer, long number, int radix);

int
s_to_i(char* buffer);

int
char_hexa_to_i(char c);

#endif
