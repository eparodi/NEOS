#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <net.h>

#define MAC_ADDRESS_SIZE 17

int
check_mac(const char * command, unsigned char * mac);

void
print_mac() {
  unsigned char mac_addr[6];
  _get_mac(mac_addr);
  int i;
  for ( i = 0 ; i < 6 ; i++){
    printf("%x",mac_addr[i]);
    if (mac_addr[i] < 0x10){
      printf("0");
    }
    if ( i != 5 ){
      printf(":");
    }
  }
  printf("\n");
}

void
send_message_broadcast(const char * message) {
  unsigned char dest_mac[6] = { 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF };
  int size = strlen(message);
  _send_message(dest_mac,message,size);
}

void
msg_shell(const char * command){
  unsigned char mac[6];
  int size,length;
  size = check_mac(command, mac);
  if ( size == -1 ){
    printf("La direccion mac es incorrecta.\n");
    return;
  }
  length = strlen(command + size + 1);
  _send_message(mac,command + size + 1,length);
}

int
check_mac(const char * command, unsigned char * mac) {
  int i = 0;
  char c;
  int size = 0;
  int current = 0;
  int j;
  unsigned char num;

  while ( command[i] == ' '){
    i++;
  }
  j = i;
  while( i < j + MAC_ADDRESS_SIZE){
    c = command[i++];
    switch(c){
      case ':':
        if ( size > 2 ){
          return -1;
        }else{
          size = 0;
          current++;
        }
        break;
      default:
        if ( !is_hexa(c) || size > 2 ){
          return -1;
        }else{
          if ( size == 0 ){
            num = char_hexa_to_i(c) * 0x10;
          }else{
            num += char_hexa_to_i(c);
            mac[current] = num;
          }
          size++;
        }
    }
  }

  return i;
}
