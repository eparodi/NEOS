#include "include/stdio.h"
#include "include/shell.h"
#include "include/stdlib.h"

void
start_shell(){

  //clearScreen();



//  printf("Bienvenido a NEOS, para un breve resumen de las funcionalidades se encuentra disponible el comando help");
  char  buffer[100]={0};


int exit = -1;
int i = 0;
	do{
scanf(" Ingresa un comando %s",buffer);
if(strcmp(buffer,"eliseo")==0){
  printf(" eliseo detectado ");
}else if(strcmp(buffer,"help")==0){
  printf(" pedile ayuda a tu mama ");
}else if(strcmp(buffer,"exit")==0){
  exit = 1;
}

 }  while(exit == -1);
printf(" nos fuimos ");


}
