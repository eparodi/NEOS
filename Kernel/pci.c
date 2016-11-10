#include <pci.h>
#include <vsa_driver.h>
#include <debug.h>

/* TODO: perform this code*/

uint16_t
get_vendor_id(uint8_t bus, uint8_t dev_func){
  return _pci_read_reg(bus,dev_func,0x00);
}

uint16_t
get_devide_id(uint8_t bus, uint8_t dev_func){
  return _pci_read_reg(bus,dev_func,0x00) >> 16;
}

uint16_t
get_header_type(uint8_t bus, uint8_t dev_func){
  return _pci_read_reg(bus,dev_func,0x0C) >> 16 ;
}

void
print_all_devices(){
  int i,j,size;
  uint16_t vendorID;
  uint16_t deviceID;
  uint16_t hType;
  uint32_t data;
  char aux[30];
  for ( i = 0 ; i <= 0xFF ; i++ ){
    for ( j = 0 ; j <= 0xFF ; j++ ){ // j+= 0x08
      vendorID = get_vendor_id(i, j);
      if (vendorID != 0xFFFF){
        size = parse_int(aux,i,10);
        aux[size] = 0;
        print_string("Bus:",0xffffff);
        print_string(aux,0xffffff);
        print_string(",",0xffffff);
        size = parse_int(aux,j>>3,10);
        aux[size] = 0;
        print_string("Device:",0xffffff);
        print_string(aux,0xffffff);
        print_string(",",0xffffff);
        size = parse_int(aux,j&0x7,10);
        aux[size] = 0;
        print_string("Function:",0xffffff);
        print_string(aux,0xffffff);
        print_string(":",0xffffff);
        size = parse_int(aux,vendorID,16);
        aux[size] = 0;
        print_string(" VendorID: 0x",0xffffff);
        print_string(aux,0xffffff);
        deviceID = get_devide_id(i, j);
        size = parse_int(aux,deviceID,16);
        aux[size] = 0;
        print_string(", DeviceID: 0x",0xffffff);
        print_string(aux,0xffffff);
        hType = get_header_type(i,j);
        size = parse_int(aux,hType,16);
        aux[size] = 0;
        print_string(", HeaderType: 0x",0xffffff);
        print_string(aux,0xffffff);
        data = _pci_read_reg(i,j,0x04);
        size = parse_int(aux,data,16);
        aux[size] = 0;
        print_string(", DATA: 0x",0xffffff);
        print_string(aux,0xffffff);
        print_string("\n",0xffffff);
      }
    }
  }
}

void
initialize_device(uint8_t bus, uint8_t dev_func) {
  uint32_t value = _pci_read_reg(bus,dev_func,0x04);
  value |= 0x04;
  _pci_write_reg(bus,dev_func,0x04,value);

}
