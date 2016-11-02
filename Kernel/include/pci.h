#ifndef PCI_H
#define PCI_H

#include <stdint.h>
/*
 *	Gets the RAW data from the PCI.
 *	Parameters:
 *		-rdi: bus number. (bl)
 *		-rsi: device/function number. (cl)
 *		-rdx: register number. (dl)
 *	Return:
 *		rax:	register information.
 */
uint32_t
_pci_read_reg(uint8_t bus, uint8_t dev_func, uint8_t regist );

uint32_t
_pci_write_reg(uint8_t bus, uint8_t dev_func, uint8_t regist ,uint32_t data);

uint16_t
get_vendor_id(uint8_t bus, uint8_t dev_func);

uint16_t
get_devide_id(uint8_t bus, uint8_t dev_func);

void
print_all_devices();

void
initialize_device(uint8_t bus, uint8_t dev_func);

#endif
