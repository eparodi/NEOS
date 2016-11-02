#include "./include/rtl8139.h"
#include "./include/port.h"
#include "./include/types.h"
#include "./include/vsa_driver.h"
#include "./include/debug.h"
#define IOADDRESS 0xC0

// wiki.osdev.org/RTL8139

/*TODO: TEST FUNCTION, DELETE*/
int
send_message(uint8_t * data, uint32_t length);

static
byte rx_buffer[8208];

static
byte tx_buffer[8208];

void
start_rtl8139(){
  // Initializes rtl8139.
  _out_port_8( IOADDRESS + 0x52, 0x0);
  // Software reset.
  _out_port_8( IOADDRESS + 0x37, 0x10);
  while( (_in_port_8(IOADDRESS + 0x37) & 0x10) != 0) {}
  // Set buffer.
  _out_port_32( IOADDRESS + 0x30, (uint32_t) rx_buffer);
  // Set interruption mask register.
  _out_port_16( IOADDRESS + 0x3C, 0x0005);
  // Set mode.
  _out_port_8( IOADDRESS + 0x44, 0xf | (1 << 7));
  // Start Receiver and Transmiter
  _out_port_8( IOADDRESS + 0x37, 0x0C);
  send_message("Hello",5);
  print_string("We say Hello.\n",0x00ff00);
  print_mac();
}

void
rtl_irq_handler() {
  _out_port_16(IOADDRESS + 0x3E, 0x1);
}

void print_mac(){
  char aux[30];
  uint8_t data,size;
  print_string("MAC ADDRESS:\n",0xff0000);
  for ( int i = 0 ; i < 6 ; i++){
    data = _in_port_8( IOADDRESS + i);
    size = parse_int(aux,data,16);
    aux[size] = 0;
    print_string(aux,0x0000ff);
    if ( i != 5){
      print_string(":",0x0000ff);
    }
  }
  print_string("\n",0x0000ff);
}

int
send_message(uint8_t * data, uint32_t length){
  _out_port_32( IOADDRESS + 0x20, (uint32_t) data);
  _out_port_32( IOADDRESS + 0x10, (uint32_t) length);
}
