#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <termios.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <curses.h>
#include <sys/time.h>
#include <stdlib.h>
#include "main.h"



int main(void)
{
    char bomb = '*';
    
    int posX, posY;
    float speed;
    element store;
    int command,i,j,k,mposX=0,mposY=0;
    char c;
    FILE *fp;
    
    
    printf("input angle power direction(Left:1,Right:0) : ");
    scanf("%f %f %d",&store.angle,&store.power,&store.direction);
    
    if((fp=fopen("map3.bin", "rb"))==NULL){
        printf("cannot find map.txt");
        exit(1);
    }
    
    for(k=0;k<7;k++)
        for(i=0;i<10;i++){
            for(j=0;j<100;j++){
                fread(&c,sizeof(char),1,fp);
                map[i+k*10][j]=c;
            }
            fread(&c, sizeof(char), 1, fp);
        }
    

    
    speed=40000-store.power*1000*pow(cos(store.angle*PI/180.0),2);
    
    if(speed<=24000)
        speed=24000;
    
    initscr();
    init_keyboard();
    set_nodelay_mode();
    
    clear();
    
    get_screen(mposX, mposY);
    if(store.direction==0)
        posX = 5;
    else
        posX = COLS-5;
    posY = 20;
    
    move(posY, posX);
    
    while(inch()==' '){
        move(++posY,posX);
    }
    
    while(inch()=='*'){
        move(--posY, posX);
    }
    
    
    if(store.power>60)
        store.power=60;
    
    equation(&store);
    
    
    parabola(store, posX, posY, bomb);
    
    endwin();
    
    printf("coeffient a:%f coeffient b:%f angle:%f power:%f ",store.a,store.b,store.angle,store.power);
    printf("speed : %f posX : %d posY : %d %d %d %c",speed,posX,posY,COLS,LINES,inch());
    if(store.direction==1)
        printf("direction:Left \n");
    else
        printf("direction:Right \n");
    
    return 0;
}
