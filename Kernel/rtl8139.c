#include "./include/rtl8139.h"
#include "./include/port.h"
#include "./include/types.h"
#define IOADDRESS 0xC400

// wiki.osdev.org/RTL8139

static
byte buffer[8208];

void
start_rtl8139(){
  // Initializes rtl8139.
  _out_port_8( IOADDRESS + 0x52, 0x0);
  // Software reset.
  _out_port_8( IOADDRESS + 0x37, 0x10);
  while( (_in_port_8(IOADDRESS + 0x37) & 0x10) != 0) {}
  // Set buffer.
  _out_port_32( IOADDRESS + 0x30, (uint32_t) buffer);
  // Set interruption mask register.
  _out_port_16( IOADDRESS + 0x3C, 0x0005);
  // Set mode.
  _out_port_8( IOADDRESS + 0x44, 0xf | (1 << 7));
  // Start Receiver and Transmiter
  _out_port_8( IOADDRESS + 0x37, 0x0C);
}
