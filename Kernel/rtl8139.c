#include "./include/rtl8139.h"
#include "./include/port.h"
#include "./include/types.h"
#include "./include/vsa_driver.h"
#include "./include/debug.h"
#define IOADDRESS 0xC000

// wiki.osdev.org/RTL8139

/*TODO: TEST FUNCTION, DELETE*/
int
send_message(uint8_t * data, uint32_t length);

static uint8_t mac_addr[6];

static
byte rx_buffer[8208];

static
byte tx_buffer[8208];

void
start_rtl8139(){
  uint32_t data;
  // Initializes rtl8139.
  _out_port_8( IOADDRESS + 0x52, 0x0);
  // Software reset.
  _out_port_8( IOADDRESS + 0x37, 0x10);
  while( (_in_port_8(IOADDRESS + 0x37) & 0x10) ) {}
  // Set buffer.
  _out_port_32( IOADDRESS + 0x30, (uint32_t) rx_buffer);
  // Set interruption mask register.
  _out_port_16( IOADDRESS + 0x3C, 0x0005);
  // Set mode.
  _out_port_32( IOADDRESS + 0x44, 0xf | (1 << 7));
  // Start Receiver and Transmiter
  _out_port_16( IOADDRESS + 0x37, 0xFF); //0x0C
  data = _in_port_32(IOADDRESS +0x40);
  // Set DMA size.
  _out_port_32( IOADDRESS + 0x40, data | 0x07);
  // Change mode.
  _out_port_8( IOADDRESS + 0x51, 0x10);

  //print_string("We say Hello.\n",0x00ff00);
  //_out_port_32(IOADDRESS + 0x00, 0xBEEFBEEF);
  //_out_port_32(IOADDRESS + 0x04, 0x0000BEEF);
  get_mac();
  print_mac();
  print_things();
  create_and_send_custom_message();
}

void
print_things() {
  char aux[30];
  uint32_t data,size;
  data = _in_port_32(IOADDRESS + 0x44);
  size = parse_int(aux,data,16);
  aux[size] = 0;
  print_string(aux,0xFFFFFF);
  print_string("\n",0x0);
}

void
rtl_irq_handler() {
  _out_port_16(IOADDRESS + 0x3E, 0x1);
}

void
print_mac(){
  char aux[30];
  uint32_t data,size;
  print_string("MAC ADDRESS: ",0xff0000);
  for ( int i = 0 ; i < 6 ; i++){
    size = parse_int(aux,mac_addr[i],16);
    aux[size] = 0;
    print_string(aux,0x0000ff);
    mac_addr[i] = data;
    if ( i != 5){
      print_string(":",0x0000ff);
    }
  }
  print_string("\n",0x0000ff);
}

void
get_mac(){
  uint32_t data;
  data = _in_port_32(IOADDRESS);
  mac_addr[0] = data;
  mac_addr[1] = data >> 8;
  mac_addr[2] = data >> 16;
  mac_addr[3] = data >> 24;
  data = _in_port_32(IOADDRESS+0x04);
  mac_addr[4] = data;
  mac_addr[5] = data >> 8;
}

void
create_and_send_custom_message(){
  uint8_t data[100];
  uint8_t i,j;
  j = 0;
  for (i = 0 ; i < 6; i++){
    data[j] = 0xFF;
    j++;
  }
  for (i = 0; i < 6; i++ ){
    data[j] = mac_addr[i];
    j++;
  }
  data[j++] = 0x80;
  data[j++] = 0x00;
  data[j++] = 'h';
  send_message(data,100);
}

int
send_message(uint8_t * data, uint32_t length){
  uint32_t reg,size,reg_data;
  //uint32_t reg2;
  char aux[20];
  _out_port_32( IOADDRESS + 0x20, (uint32_t) data);
  size = parse_int(aux,(uint32_t) data,16);
  aux[size] = 0;
  print_string(aux,0xffffff);
  print_string("\n",0xffffff);

  _out_port_32( IOADDRESS + 0x10, 0x80000 | length);

  reg=_in_port_32(IOADDRESS+0x10);
  size = parse_int(aux,reg,16);
  aux[size] = 0;
  print_string(aux,0xffffff);
  print_string("\n",0xffffff);
  while (((reg=_in_port_32(IOADDRESS+0x10)) & 0x8000) == 0){
    /*reg2 = _in_port_32(IOADDRESS+0x60);
    size = parse_int(aux,reg2,16);
    aux[size] = 0;
    print_string(aux,0xffffff);
    print_string("\n",0xffffff);*/
  }
  size = parse_int(aux,reg& 0x8000,16);
  aux[size] = 0;
  print_string(aux,0xffffff);
  print_string("\n",0xffffff);
  print_string("The message was sent!\n",0x0000ff);
}
