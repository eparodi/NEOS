#include <stdio.h>

void
print_mac() {
  unsigned char mac_addr[6];
  _get_mac(mac_addr);
  int i;
  for ( int i = 0 ; i < 6 ; i++){
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
