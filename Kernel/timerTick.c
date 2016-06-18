#include "include/timerTick.h"
#include "include/vsa_driver.h"

typedef void (*timerEventT)() ;

unsigned int cdown[MAXCOUNTERS]={0};


static timerEventT timerEvents[MAXCOUNTERS];
static int alarmEvents[MAXCOUNTERS];


static int* sleepCounter;
static qword counter = 0;
static int timerListeners =0;


void tick(){
    counter++;
    for (int j = 0; j < timerListeners; j++) {
        if(counter % alarmEvents[j]==0) timerEvents[j]();
    }
}




void timerSleep(){
    (*sleepCounter) += 16;	// 1s/60fps = 16ms per frame
}

void sleep(int time){

    *sleepCounter=0;

    _cli();
    addTimerListener(&timerSleep,1);
    _sti();

    while(*sleepCounter<time);


    _cli();
    deleteTimerListener(&timerSleep);
    _sti();

    return;
}


void addTimerListener(timerEventT event, int interval){
    if(timerListeners >= MAXCOUNTERS) return;
    else{
        alarmEvents[timerListeners] = interval;
        timerEvents[timerListeners] = event;
        timerListeners++;
    }
}

void deleteTimerListener(timerEventT event){
    for (int j = 0; j < timerListeners; j++) {
        if(timerEvents[j]==event){
            timerListeners--;
            for(int k=0;k<timerListeners;k++){
                timerEvents[k]=timerEvents[k+1];
                alarmEvents[k]=alarmEvents[k+1];
            }
            break;
        }
    }
}
