
#include "include/timerTick.h"
#include "include/vsa_driver.h"


void drawr(int x, int y,int siz,int state,int color){
    if(siz<5) return;
    if(state==0) return;
    int xi,yi,t;
    int v,w;
    t=siz/3;
    xi=x+t;
    yi=y+t;
    draw_filled_rectangle(xi,yi,xi+t,yi+t,color);
    drawr(x,y,t,state-1,color);
    drawr(x+t,y,t,state-1,color);
    drawr(x+t+t,y,t,state-1,color);
    drawr(x,y+t,t,state-1,color);
    drawr(x,y+t+t,t,state-1,color);
    drawr(x+t,y+t+t,t,state-1,color);
    drawr(x+t+t,y+t,t,state-1,color);
    drawr(x+t+t,y+t+t,t,state-1,color);
}
void drawFractalc(int x, int y,unsigned int siz,unsigned int color){
    int xi,yi,t;
    int pasos=5;
    int i,j,p;
    t=siz/3;
    xi=x+t;
    yi=y+t;
    draw_filled_rectangle(xi,yi,xi+t,yi+t,color);
    for(p=0;p<pasos;p++) {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                drawr(x + t * i, x + t * j, t, p,color);
            }
        }
        sleep(152);
    }

}

void drawFractal(int x, int y,unsigned int siz){
    drawFractalc(x,y,siz,0x0000FF);
}