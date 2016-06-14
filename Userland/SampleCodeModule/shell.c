#include "/home/osboxes/NEOS/Kernel/include/videoDriver.h"
#include <stdio.h>
#include "include/shell.h"
void
start_shell(){
  clearScreen();
  printf("Bienvenido a NEOS, para un breve resumen de las funcionalidades se encuentra disponible el comando help" );
  char  buffer[10]={0};
  //printf("Lei: ");
do{
  read(0,buffer,1);
}  while(buffer[0]=='j');
  putchar(buffer[0]);
}
