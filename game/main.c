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

int mposY=0,mposX=0,msizeX=0,msizeY=0;

void set_mpos(int posX,int posY){
    if(posY+5>=msizeY)
        mposY=msizeY-LINES;
    else if(posY+5-LINES<0)
        mposY=0;
    else
        mposY=posY+5-LINES;
    if(COLS>msizeX)
        mposX=0;
    else if(posX-COLS/2<0)
        mposX=0;
    else if(posX+COLS/2>msizeX){
        mposX=msizeX-COLS;
    }
    else
        mposX=posX-COLS/2;
}

int main(void)
{
    char bomb = '*';
    
    int posX, posY;
    float speed;
    element store;
    int command,i,j;
    char c;
    FILE *fp;
    
    
    printf("input angle power direction(Left:1,Right:0) : ");
    scanf("%f %f %d",&store.angle,&store.power,&store.direction);
    
    if(store.angle>=90){
        store.angle=89.0;
    }
    
    if((fp=fopen("map3.txt", "r"))==NULL){
        printf("cannot find map.txt");
        exit(1);
    }
    
    fscanf(fp, "%d %d\n",&msizeX,&msizeY);
    
    for(i=0;i<msizeY;i++){
        for(j=0;j<msizeX;j++){
            c=fgetc(fp);
            map[i][j]=c;
        }
        fgetc(fp);
    }
    
    
    
    speed=40000-store.power*1000*pow(cos(store.angle*PI/180.0),2);
    
    if(speed<=24000)
        speed=24000;
    
    initscr();
    init_keyboard();
    set_nodelay_mode();
    
    clear();
    //startmenu();
    
    if(store.direction==0)
        posX = 5;
    else
        posX = msizeX-5;
    posY = 20;
    
    move(posY, posX);
    
    while(map[posY][posX]==' '){
        posY++;
    }
    
    while(map[posY][posX]=='*'){
        posY--;
    }
    
    set_mpos(posX, posY);
    
    get_screen(mposX, mposY);
    refresh();
    
    if(store.power>60)
        store.power=60;
    
    equation(&store);
    parabola(store, posX, posY, bomb);
    
    endwin();
    
    printf("coeffient a:%f coeffient b:%f angle:%f power:%f ",store.a,store.b,store.angle,store.power);
    printf("speed : %f posX : %d posY : %d Col: %d LINE : %d mapX: %d mapY: %d",speed,posX,posY,COLS,LINES,mposX,mposY);
    if(store.direction==1)
        printf("direction:Left \n");
    else
        printf("direction:Right \n");
    
    return 0;
}
