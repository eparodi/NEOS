#include <port.h>
#include <rtl_driver.h>
#include <vsa_driver.h>
#include <debug.h>

#define MAC_ADDRESS_LENGTH 6
#define IOADDRESS 0xC000
#define IRQ_ROK_REG 0x0001
#define IRQ_TOK_REG 0x0004

typedef struct rtl_t{
  uint8_t rx_buffer[8208];
  uint8_t tx_buffer[2048][4];
  uint8_t mac_addr[6];
  uint8_t tx_num; // the number of the buffer to write. From 0 to 3
}rtl_t;

static rtl_t rtl_info;

void
start_rtl() {
  // Initializes rtl_info:
  rtl_info.tx_num = 0;

  // Initializes rtl8139.
  _out_port_8( IOADDRESS + 0x52, 0x0);
  // Software reset.
  _out_port_8( IOADDRESS + 0x37, 0x10);
  while( (_in_port_8(IOADDRESS + 0x17) & 0x10) ) {}

  _out_port_32( IOADDRESS + 0x40, 0x03000700);
  // Set Receiver Mode.
  _out_port_32( IOADDRESS + 0x44, 0x3f | (1 << 7));
  // Set Receiver and Transmiter buffer.
  _out_port_32( IOADDRESS + 0x30, (uint32_t) rtl_info.rx_buffer);
  _out_port_32( IOADDRESS + 0x20, (uint32_t) &rtl_info.tx_buffer[0][0]);
  _out_port_32( IOADDRESS + 0x24, (uint32_t) &rtl_info.tx_buffer[1][0]);
  _out_port_32( IOADDRESS + 0x28, (uint32_t) &rtl_info.tx_buffer[2][0]);
  _out_port_32( IOADDRESS + 0x2C, (uint32_t) &rtl_info.tx_buffer[3][0]);
  // Set interruptions.
  _out_port_16( IOADDRESS + 0x3C , 0x000F );
  // Start Receiver and Transmiter
  _out_port_8( IOADDRESS + 0x37, 0x0C);

  get_mac();
}

void
get_mac(){
  uint32_t data;
  data = _in_port_32(IOADDRESS);
  rtl_info.mac_addr[0] = data;
  rtl_info.mac_addr[1] = data >> 8;
  rtl_info.mac_addr[2] = data >> 16;
  rtl_info.mac_addr[3] = data >> 24;
  data = _in_port_32(IOADDRESS+0x04);
  rtl_info.mac_addr[4] = data;
  rtl_info.mac_addr[5] = data >> 8;
}

uint8_t broadcast_mac[6] = { 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF };

void
sendCustomPackage() {
  Package pkg;
  uint8_t mac[6] = { 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF };

  pkg.data = "SON TODOS PUTOS, VIVA PERON LA CONCHA DE TU HERMANA! MAKE AMERICA GREAT AGAIN";
  pkg.length = 78;
  pkg.mac_dest = mac;
  send_message(&pkg);
}

void
send_message(Package * data) {
  uint16_t status_address = IOADDRESS + 0x10 + rtl_info.tx_num * 0x04;
  uint16_t length = data-> length + MAC_ADDRESS_LENGTH * 2 + 2;
  uint8_t * buf = rtl_info.tx_buffer[rtl_info.tx_num];

  // waits until the previous package is free.
  while (!(_in_port_32(status_address) & 0x2000)){}

  mem_cpy(&buf[0],data->mac_dest,MAC_ADDRESS_LENGTH);
  mem_cpy(&buf[MAC_ADDRESS_LENGTH],rtl_info.mac_addr,MAC_ADDRESS_LENGTH);
  mem_cpy(&buf[MAC_ADDRESS_LENGTH * 2],&(data->length),2);
  mem_cpy(&buf[MAC_ADDRESS_LENGTH * 2 + 2],data->data,data->length);
  _out_port_32(status_address,length);
  rtl_info.tx_num++;
  rtl_info.tx_num &= 0x03;
}

void
mem_cpy(uint8_t * buffer, uint8_t * cpy, uint64_t length){
  for ( int i = 0 ; i < length ; i++ ){
    buffer[i] = cpy[i];
  }
}

void
copy_mac(uint8_t * buffer) {
  mem_cpy(buffer, rtl_info.mac_addr,6);
}

void
print_debug() {
  int size;
  uint16_t data;
  char aux[30]={1};

  data = _in_port_16(IOADDRESS + 0x3E);
  size = parse_int(aux,data,10);
  aux[size] = 0;
  print_string(data,0xffffff);
  print_string("\n",0xffffff);
  print_string(rtl_info.rx_buffer,0xffffff);
}

void
rtl_irq_handler() {
  uint16_t check_int = _in_port_16(IOADDRESS + 0x3E);
  int size;
  char aux[30];
  if ( (check_int & IRQ_ROK_REG ) != 0){
    int color_msj=0xff0000;
    //VERIFICA SI ES WHISP O BROADCASTT
    int pos_mac=0;
    int whisp=0;
    int broad=0;
    for ( int i = 4 ; i < 10 ; i++ ){
      size = parse_int(aux,rtl_info.rx_buffer[i],16);
      aux[size] = 0;
      char aux2[30];
      int size2;
      size2 = parse_int(aux2,rtl_info.mac_addr[pos_mac],16);
      aux2[size2]=0;
      if(aux[0]==aux2[0]){
          whisp++;
      }
      size2=parse_int(aux2,broadcast_mac[pos_mac],16);
      aux[size2]=0;
      if(aux[0]==aux2[0]){
          broad++;
      }
      pos_mac++;
    }
    if(whisp==5){
       color_msj=0xFF69b4;
    }
    if(broad>3){
       color_msj=0xFFA500;
    }
    print_string("\n",0x000000);
    print_string("Mensaje de ",color_msj);
    for ( int i = 10 ; i < 16 ; i++ ){
      size = parse_int(aux,rtl_info.rx_buffer[i],16);
      aux[size] = 0;
      print_string(aux,color_msj);
    }
    print_string("\n", 0xff0000);
    print_string(&rtl_info.rx_buffer[MAC_ADDRESS_LENGTH * 2 + 6],color_msj);
    //print_string(&rtl_info.rx_buffer[MAC_ADDRESS_LENGTH * 2 + 6 +20],0xff0000);
    print_string("\n",0);
    _out_port_16(IOADDRESS + 0x3E, IRQ_ROK_REG);
    //_out_port_16(IOADDRESS + 0X37, 0x04);
    //print_debug();
    start_rtl();
  }else if ( (check_int & IRQ_TOK_REG) != 0){
    print_string("ENVIADO\n",0x0000ff);
    _out_port_16(IOADDRESS + 0x3E, IRQ_TOK_REG);
    start_rtl();
  }else {
    print_string("Error Code: ", 0x00ff00);
    size = parse_int(aux,check_int,16);
    aux[size] = 0;
    print_string(aux,0xffffff);
    print_string("\n",0xffffff);
  }
  _out_port_8(0xA0,0x20);
}
