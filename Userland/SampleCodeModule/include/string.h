#ifndef STRING_H
#define STRING_H

/*
 * Compares n characters of two strings.
 * Parameters:
 *  str1 and str2
 *  n: the number of characters to compare.
 * Return : 1 if str1 is lexically greater than str 2, -1 if str2 is greater than
 * str1 and 0 if they are equal.
 */
 int
 strncmp( const char * str1 , const char * str2 , int length );

 int
 strlen( const char * str );

 /*
  * Compares two strings
  * Parameters:
  *  str1 and str2
  * Return : 1 if str1 is lexically greater than str 2, -1 if str2 is greater than
  * str1 and 0 if they are equal.
  */
 int
 strcmp(const char * str1,const char * str2);

 int
 is_hexa(const char ch);

#endif
