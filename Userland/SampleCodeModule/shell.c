#include "include/stdio.h"
#include "include/shell.h"
#include "include/stdlib.h"

void
start_shell(){
    int k;
  //clearScreen();
  printf("Bienvenido a NEOS, para un breve resumen de las funcionalidades se encuentra disponible el comando help", NULL);
  char  buffer[10]={0};
  
  //printf("Lei: ");
int exit = -1;
	do{
	  k = read(0,buffer,1);

    if(k != 0 ){
     printf(" Lei esto ",NULL);
      printf(buffer,NULL);


    }
	}  while(exit ==-1);



}
