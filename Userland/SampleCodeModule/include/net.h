#ifndef NET_H
#define NET_H

void
_get_mac(unsigned char * buffer);

void
_send_message(const unsigned char * mac, const char * message, int length);

void
print_mac();

void
send_message_broadcast(const char * message);

void
msg_shell(const char * command);

#endif
