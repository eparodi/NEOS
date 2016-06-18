#include "include/timerTick.h"
#include "include/vsa_driver.h"
#include "include/lib.h"

#include "include/strings.h"

static unsigned int cdown[MAXCOUNTERS];

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
    char buf[10];
    if(x==NOT) return;
    while(getTimer(x)!=0){
        intToString(buf, getTimer(x));
        print_string(buf,0xffffff);
    }
        //_hlt(); NO SE PORQUE PERO SI LO PONGO CRASHEA,PRUEBENLO
    return;
}

void tick(){
    int i;
    for(i=0;i<MAXCOUNTERS;i++) {
        if (cdown[i] > 0)
            cdown[i]--;
    }
}
