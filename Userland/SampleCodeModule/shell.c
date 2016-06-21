#include "include/stdio.h"
#include "include/shell.h"
#include "include/stdlib.h"
#include "include/time.h"

void
draw_fractal(int,int,int,int);


void
start_shell(){
//  char * buffer = malloc(1000);
char buffer[1000]={0};
  buffer[0] = 0;
  int exit = -1;
  int i = 6;
  int x,y,size;
	do{
    printf("$> ");
    scanf("%s",buffer);
    if(strcmp(buffer,"help")==0){
      printf("Comandos de NEOShell:\n");
      printf("clear          : Borra la pantalla.\n");
      printf("date           : Muestra la fecha actual.\n");
      printf("echo [message] : Muestra una linea de texto [message].\n");
      printf("exit           : Cierra la consola.\n");
      printf("fractal        : Muestra un fractal en xla pantalla.\n");
      printf("help           : Muestra el manual de ayuda.\n");
      printf("hour           : Muestra la hora actual.\n");
      printf("sleep          : La consola espera durante un tiempo.\n");
    }else if(strcmp(buffer,"exit")==0){
      exit = 1;
    }else if(strncmp(buffer,"echo ",5)==0){
      printf("%s\n",buffer+5);
    }else if(strcmp(buffer,"hour")==0){
      printf("%s\n", get_hour());
    }else if(strcmp(buffer,"date")==0){
      printf("%s\n", get_date());
    }else if(strcmp(buffer,"fractal")==0){
      int* a=0x500000;
      cls();
      draw_fractal(1,1,768,*a);
      sleep(300);
      cls();
    }else if(strcmp(buffer,"clear")==0){
      cls();
    }else if(strcmp(buffer,"sleep")==0){
      sleep(3000);
      printf("Dormi 10 segundos.\n");
    }else{
      printf("No existe ese comando, use help para aclarar sus dudas.\n");
    }
 }  while(exit == -1);
  printf(" Ahora puede apagar el equipo.");
}
