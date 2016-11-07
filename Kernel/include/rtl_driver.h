#ifndef RLTDRIVER_H
#define RTLDRIVER_H

typedef struct Package{
  uint8_t * data;
  uint8_t * mac_dest;
  uint16_t length;
} Package;

void
start_rtl();

void
mem_cpy(uint8_t * buffer, uint8_t * cpy, uint64_t length);

void
send_message(Package * data);

#endif
