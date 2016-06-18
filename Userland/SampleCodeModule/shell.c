#include "include/stdio.h"
#include "include/shell.h"
#include "include/stdlib.h"
#include "include/time.h"

void
start_shell(){
  char * buffer = malloc(1000);
  buffer[0] = 0;
  int exit = -1;
  int i = 6;
	do{
    printf("$> ");
    scanf("%s",buffer);
    if(strcmp(buffer,"help")==0){
      printf(" pedile ayuda a tu mama\n");
    }else if(strcmp(buffer,"exit")==0){
      exit = 1;
    }else if(strncmp(buffer,"echo ",5)==0){
      printf("%s\n",buffer+5);
    }else if(strcmp(buffer,"hour")==0){
      printf("%s\n", get_hour());
    }else if(strcmp(buffer,"date")==0){
      printf("%s\n", get_date());
    }else if(strcmp(buffer,"fractal")==0){
      draw_fractal(2,2,768);
    }else if(strcmp(buffer,"clear")==0){
      cls();
    }else if(strcmp(buffer,"sleep")==0){
      sleep(10000);
      printf("Dormi 10 segundos.\n");
    }
 }  while(exit == -1);
  printf(" nos fuimos ");
}
