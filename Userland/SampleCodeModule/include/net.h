#ifndef NET_H
#define NET_H

void
_get_mac(unsigned char * buffer);

void
_send_message(const unsigned char * mac, const char * message, int length);

void
print_mac();

#endif
