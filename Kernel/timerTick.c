#include "include/timerTick.h"
#include "include/vsa_driver.h"
#include "include/lib.h"


typedef void (*event)() ;

static unsigned int cdown[MAXCOUNTERS];



void rem(int i){
    cdown[i]--;
}


void tick(){
    for(int i=0;i<MAXCOUNTERS;i++){
        if(cdown[i]>0){
            rem(i);
        }
    }
}

int addTick(int t){
    for(int i=0;i<MAXCOUNTERS;i++) {
        if (cdown[i] == 0) {
            cdown[i] = t;
            return i;
        }
    }
    return -1;
}

void sleep(int t){
    _cli();
    int x=addTick(t);
    _sti();
    while(cdown[x]>0);
}
