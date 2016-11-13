#include <string.h>

int
strncmp( const char * str1 , const char * str2 , int length ){
	int i, aux;
	for ( i = 0; i < length ; i++ ){
		aux = str1[i] - str2[i];
		if ( aux ){
			return aux;
		}
	}
	return 0;
}

int
strcmp(const char * str1,const char * str2){
	int i, aux;
	for ( i = 0; str1[i]!=0 || str2[i]!=0 ; i++ ){
		aux = str1[i] - str2[i];
		if ( aux ){
			return aux;
		}

	}

	return str1[i]-str2[i];
}

int
strlen( const char * str ){
	int size = 0;
	while( str[size++] != '\0' ){}
	return size-1;
}

int
is_hexa(const char ch){
  if ( (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f' )){
    return 1;
  }else{
    return 0;
  }
}
