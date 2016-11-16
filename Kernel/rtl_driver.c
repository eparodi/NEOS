#include <port.h>
#include <rtl_driver.h>
#include <vsa_driver.h>
#include <debug.h>
#include <keyboard.h>

#define MAC_ADDRESS_LENGTH 6
#define IOADDRESS      0xC000
//IRQ
#define IRQ_ROK_REG    0x0001
#define IRQ_TOK_REG    0x0004

//BUFFER
#define RX_BUFFER_SIZE 0x2000 // 8KB
#define TX_BUFFER_SIZE 0x2048

//PIC
#define PIC_SLAVE_ADDR 0xA0
#define PIC_ACKNOW     0x20

//REGISTERS
#define RTL_TSAD_1     0x20
#define RTL_TSAD_2     0x24
#define RTL_TSAD_3     0x28
#define RTL_TSAD_4     0x2C
#define RTL_RVAD       0x30
#define RTL_COMMANDER  0x37
#define RTL_IMR        0x3C
#define RTL_ISR        0x3E
#define RTL_TX_CONFIG  0x40
#define RTL_RX_CONFIG  0x44
#define RTL_CONFIG_1   0x52

typedef struct rtl_t{
  uint8_t rx_buffer[RX_BUFFER_SIZE];
  uint8_t tx_buffer[TX_BUFFER_SIZE][4];
  uint8_t mac_addr[MAC_ADDRESS_LENGTH];
  uint8_t tx_num;      // the number of the buffer to write. From 0 to 3
  uint16_t rx_index;   // the current receiver index.
}rtl_t;

static rtl_t rtl_info;

void
print_mac(uint8_t * mac_dir, uint32_t color);

void
get_mac();

void
start_rtl() {

  //Addresses
  uint32_t ad1 = (uint32_t) &rtl_info.tx_buffer[0][0];
  uint32_t ad2 = (uint32_t) &rtl_info.tx_buffer[1][0];
  uint32_t ad3 = (uint32_t) &rtl_info.tx_buffer[2][0];
  uint32_t ad4 = (uint32_t) &rtl_info.tx_buffer[3][0];
  uint32_t adrx = (uint32_t) rtl_info.rx_buffer;
  // Initializes rtl_info:
  rtl_info.tx_num = 0;
  rtl_info.rx_index = 0;

  // Initializes rtl8139.
  _out_port_8( IOADDRESS + RTL_CONFIG_1, 0x0);
  // Software reset.
  _out_port_8( IOADDRESS + RTL_COMMANDER, 0x10);
  while( (_in_port_8(IOADDRESS + RTL_COMMANDER) & 0x10) ) {}

  _out_port_32( IOADDRESS + RTL_TX_CONFIG, 0x03000700);
  // Set Receiver Mode.
  _out_port_32( IOADDRESS + RTL_RX_CONFIG, 0x3f | (1 << 7));
  // Set Receiver and Transmiter buffer.
  _out_port_32( IOADDRESS + RTL_RVAD, adrx);
  _out_port_32( IOADDRESS + RTL_TSAD_1, ad1);
  _out_port_32( IOADDRESS + RTL_TSAD_2, ad2);
  _out_port_32( IOADDRESS + RTL_TSAD_3, ad3);
  _out_port_32( IOADDRESS + RTL_TSAD_4, ad4);
  // Set interruptions.
  _out_port_16( IOADDRESS + RTL_IMR , 0x000F );
  // Start Receiver and Transmiter
  _out_port_8( IOADDRESS + RTL_COMMANDER, 0x0C);

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

void
send_message(Package * data) {
  uint16_t status_address = IOADDRESS + 0x10 + rtl_info.tx_num * 0x04;
  uint16_t length = data-> length + MAC_ADDRESS_LENGTH * 2 + 2;
  uint8_t * buf = rtl_info.tx_buffer[rtl_info.tx_num];

  // waits until the previous package is free.
  while (!(_in_port_32(status_address) & 0x2000)){}

  mem_cpy(&buf[0],data->mac_dest,MAC_ADDRESS_LENGTH);
  mem_cpy(&buf[MAC_ADDRESS_LENGTH],rtl_info.mac_addr,MAC_ADDRESS_LENGTH);
  mem_cpy(&buf[MAC_ADDRESS_LENGTH * 2],(uint8_t*)&(data->length),2);
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
rtl_irq_handler() {
  uint16_t check_int = _in_port_16(IOADDRESS + RTL_ISR);
  int size;
  char aux[30];

  if ( (check_int & IRQ_ROK_REG ) != 0){
    erase_cursor();
    //rtl_receive();
    int color_msj=0xff0000;
    //VERIFICA SI ES WHISP O BROADCASTT
    int whisp=1;
    int broad=1;
    uint8_t * dest_mac = &rtl_info.rx_buffer[4];
    for ( int i = 0 ; i < MAC_ADDRESS_LENGTH; i++){
      if ( whisp ){
        if ( dest_mac[i] != rtl_info.mac_addr[i] ){
          whisp = 0;
        }
      }
      if ( broad ){
        if ( dest_mac[i] != 0xFF ){
          broad = 0;
        }
      }
    }
    if(whisp){
       color_msj=0xFF69b4;
    }else if(broad){
       color_msj=0xFFA500;
    }else{
      _out_port_16(IOADDRESS + 0x3E, IRQ_ROK_REG);
      start_rtl();
      _out_port_8(PIC_SLAVE_ADDR,PIC_ACKNOW);
      return;
    }

    print_string("\n",0x000000);
    print_string("Mensaje de ",color_msj);
    print_mac(&rtl_info.rx_buffer[10],color_msj);

    print_string("\n", 0xff0000);
    print_string((char *)&rtl_info.rx_buffer[MAC_ADDRESS_LENGTH * 2 + 6],color_msj);
    //print_string(&rtl_info.rx_buffer[MAC_ADDRESS_LENGTH * 2 + 6 +20],0xff0000);
    print_string("\n",0);
    restart_line();
    _out_port_16(IOADDRESS + RTL_ISR, IRQ_ROK_REG);
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
  _out_port_8(PIC_SLAVE_ADDR,PIC_ACKNOW);
}

void
print_mac(uint8_t * mac_dir, uint32_t color){
  int size;
  char aux[30];
  for ( int i = 0 ; i < MAC_ADDRESS_LENGTH ; i++ ){
    size = parse_int(aux, mac_dir[i], 16);
    if ( size == 1 ){
      print_string("0", color);
    }
    aux[size] = 0;
    print_string(aux, color);
    if ( i != 5 ){
      print_string(":", color);
    }
  }
}

int
check_my_mac(uint8_t * mac){
  int i;
  for ( i = 0 ; i < MAC_ADDRESS_LENGTH; i++ ){
    if ( mac[i] != rtl_info.mac_addr[i] ){
      return 0;
    }
  }
  return 1;
}
