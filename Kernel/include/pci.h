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


uint16_t
get_vendor_id(uint8_t bus, uint8_t dev_func);

#endif
