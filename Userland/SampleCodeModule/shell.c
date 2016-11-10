#include "include/stdio.h"
#include "include/shell.h"
#include "include/stdlib.h"
#include "include/time.h"
#include "include/net.h"

void
start_shell(){
char buffer[MAX_SIZE]={0};
  buffer[0] = 0;
  int exit = -1;

	do{
    printf("$> ");
    scanf("%s",buffer);
    if(strcmp(buffer,"help")==0){
      printf("Comandos de NEOShell:\n");
      printf("clear          : Borra la pantalla.\n");
      printf("date           : Muestra la fecha actual.\n");
      printf("echo [message] : Muestra una linea de texto [message].\n");
      printf("exit           : Cierra la consola.\n");
      printf("help           : Muestra el manual de ayuda.\n");
      printf("hour           : Muestra la hora actual.\n");
      printf("sleep          : La consola espera durante un tiempo.\n");
      printf("mac            : Devuelve la direccion mac del dispositivo.\n");
    }else if(strcmp(buffer,"exit")==0){
      exit = 1;
    }else if(strncmp(buffer,"echo ",5)==0){
      printf("%s\n",buffer+5);
    }else if(strcmp(buffer,"hour")==0){
      printf("%s\n", get_hour());
    }else if(strcmp(buffer,"date")==0){
      printf("%s\n", get_date());
    }else if(strcmp(buffer,"clear")==0){
      cls();
    }else if(strcmp(buffer,"sleep")==0){
      sleep(2400);
      printf("Dormi 10 segundos.\n");
    }else if(strcmp(buffer,"mac")==0){
      printf("MAC ADDRESS: ");
      print_mac();
    }else if(strncmp(buffer,"wall ",5)==0){
      send_message_broadcast(buffer+5);
    }else{
      printf("No existe ese comando, use help para aclarar sus dudas.\n");
    }
 }  while(exit == -1);
  printf(" Ahora puede apagar el equipo.");
}
