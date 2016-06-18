#include "include/timerTick.h"
#include "include/vsa_driver.h"

unsigned int cdown[MAXCOUNTERS]={0};


int addTimer(int r){
    int i;
    for(i=0;i<MAXCOUNTERS;i++) {
        if (cdown[i] == 0) {
            cdown[i]=r;
            return i;
        }
    }
    return NOT;
}

int getTimer(int inx){
    return cdown[inx];
}

void sleep(int time){
    int x=addTimer(time);
    if(x==NOT) return;
    while(getTimer(x)>0)
        //_hlt(); //NO SE PORQUE PERO SI LO PONGO CRASHEA,PRUEBENLO
    return;
}

void tick(){
    int i;
    for(i=0;i<MAXCOUNTERS;i++) {
        if (cdown[i] > 0)
            cdown[i]--;
    }
}
