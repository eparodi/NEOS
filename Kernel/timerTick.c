#include "include/timerTick.h"
#include "include/vsa_driver.h"
#include "include/lib.h"


typedef void (*event)() ;

static unsigned int* cdown[MAXCOUNTERS];

//static event timerEvents[MAXCOUNTERS];
//static int alarmEvents[MAXCOUNTERS];
//static int* sleepCounter;
////static qword counter = 0;
//static int timerListeners =0;

//
//void tick(){
//    counter++;
//    for (int j = 0; j < timerListeners; j++) {
//        if(counter % alarmEvents[j]==0) timerEvents[j]();
//    }
//}

void rem(int i){
    cdown[i]--;
}


void tick(){
    int flag=0;
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


//
//void timerSleep(){
//    (*sleepCounter) += 16;
//}
//
////void sleep(int time){
////    *sleepCounter=0;
////    _cli();
////    addTimerListener(&timerSleep,1);
////    _sti();
////    while(*sleepCounter<time);
////    _cli();
////    deleteTimerListener(&timerSleep);
////    _sti();
////    return;
////}
//
//
//void addTimerListener(event e, int interval){
//    if(timerListeners >= MAXCOUNTERS) return;
//    else{
//        alarmEvents[timerListeners] = interval;
//        timerEvents[timerListeners] = e;
//        timerListeners++;
//    }
//}
//
//void deleteTimerListener(event e){
//    for (int j = 0; j < timerListeners; j++) {
//        if(timerEvents[j]==e){
//            timerListeners--;
//            for(int k=0;k<timerListeners;k++){
//                timerEvents[k]=timerEvents[k+1];
//                alarmEvents[k]=alarmEvents[k+1];
//            }
//            break;
//        }
//    }
/*}*/