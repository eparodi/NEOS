#ifndef TIMERTICK_H
#define TIMERTICK_H

#include "irq.h"

void sleep(int time);
void tick();
void setTick();
#define MAXCOUNTERS 12
#define NOT -1


#endif
