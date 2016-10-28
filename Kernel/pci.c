#include <pci.h>
#include <vsa_driver.h>
#include <debug.h>

uint16_t
get_vendor_id(uint8_t bus, uint8_t dev_func){
  return _pci_read_reg(bus,dev_func,0);
}

uint16_t
get_devide_id(uint8_t bus, uint8_t dev_func){
  return _pci_read_reg(bus,dev_func,0) >> 16;
}

void
print_all_devices(){
  int i,j,size;
  uint16_t vendorID;
  uint16_t deviceID;
  char aux[30];
  for ( int i = 0 ; i <= 0xFF ; i++ ){
    for ( int j = 0 ; j <= 0xFF ; j+= 0x08 ){
      vendorID = get_vendor_id(i, j);
      if (vendorID != 0xFFFF){
        size = parse_int(aux,i,10);
        aux[size] = 0;
        print_string("Bus:",0xffffff);
        print_string(aux,0xffffff);
        print_string(",",0xffffff);
        size = parse_int(aux,j,10);
        aux[size] = 0;
        print_string("Device:",0xffffff);
        print_string(aux,0xffffff);
        print_string(": 0x",0xffffff);
        size = parse_int(aux,vendorID,16);
        aux[size] = 0;
        print_string(" VendorID:",0xffffff);
        print_string(aux,0xffffff);
        deviceID = get_devide_id(i, j);
        size = parse_int(aux,deviceID,16);
        aux[size] = 0;
        print_string(", DeviceID: 0x",0xffffff);
        print_string(aux,0xffffff);
        print_string("\n",0xffffff);
      }
    }
  }
  print_string("C'est fini! :)\n", 0xffffff);
}
