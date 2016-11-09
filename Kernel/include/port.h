#ifndef PORT_H
#define PORT_H

#include <stdint.h>

void
_out_port_8(uint16_t address, uint8_t value);

void
_out_port_16(uint16_t address, uint16_t value);

void
_out_port_32(uint16_t address, uint32_t value);

uint8_t
_in_port_8(uint16_t address);

uint16_t
_in_port_16(uint16_t address);

uint32_t
_in_port_32(uint16_t address);

#endif
