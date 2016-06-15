#include "include/stdio.h"
#include "include/shell.h"
#include "include/stdlib.h"

void
start_shell(){
    unsigned int k;
  //clearScreen();



  printf("Bienvenido a NEOS, para un breve resumen de las funcionalidades se encuentra disponible el comando help");
  char  buffer[10]={0};


  //printf("Lei: ");
int exit = -1;
int i = 0;
	do{
	  k = read(0,buffer+i*sizeof(char),1);

    if(k != 0 ){
      if(buffer[i]=='z'){
          buffer[i]=0;
          printf(buffer,NULL );

      }
       i++;

   }
 }  while(exit == -1);



}
