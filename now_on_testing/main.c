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
int p1[2], p2[2];

void set_mpos(int posX,int posY){
    if(posY+5>=msizeY)
        mposY=msizeY-MAP_Y;
    else if(posY+5-MAP_Y<0)
        mposY=0;
    else
        mposY=posY+5-MAP_Y/2;
    if(MAP_X>msizeX)
        mposX=0;
    else if(posX-MAP_X/2<0)
        mposX=0;
    else if(posX+MAP_X/2>msizeX){
        mposX=msizeX-MAP_X;
    }
    else
        mposX=posX-MAP_X/2;
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
    
    for(i=0;i<msizeY;i++)
    {
        for(j=0;j<msizeX+1;j++)
        {
            c = fgetc(fp);
            if(c == '#')
            {
                map[i][j] = c;
            }
            else if(c == '1')
            {
                p1[0] = i;
                p1[1] = j;
                map[i][j] = ' ';
            }
            else if(c == '2')
            {
                p2[0] = i;
                p2[1] = j;
                map[i][j] = ' ';
            }
            else if(c == ' ')
            {
                map[i][j] = c;
            }
        }
    }
    
    speed=40000-store.power*1000*pow(cos(store.angle*PI/180.0),2);
    
    if(speed<=24000)
        speed=24000;
    
    initscr();
    init_keyboard();
    set_nodelay_mode();
    
    clear();
    //startmenu();
    move(0,0);
    for(i=0;i<=MAP_X+1;i++)
    {
        move(0,i);
        addch('&');
    }
    for(i=1;i<=MAP_Y;i++)
    {
        move(i,0);
        addch('&');
        move(i,MAP_X+1);
        addch('&');
    }
    move(MAP_Y+1,0);
    
    for(i=0;i<=MAP_X+1;i++)
    {
        move(MAP_Y+1,i);
        addch('&');
    }
    refresh();
    
    if(store.direction==0)
    {
        posX = p1[1];
        posY = p1[0];
    }
    else
    {
        posX = p2[1];
        posY = p2[0];
    }
    move(posY, posX);
    
    while(map[posY][posX]==' '){
        posY++;
    }
    
    while(map[posY][posX]=='#'){
        posY--;
    }
    
    set_mpos(posX, posY);
    
    get_screen(mposX, mposY,msizeX,msizeY);
    refresh();
    
    if(store.power>60)
        store.power=60;
    
    equation(&store);
    parabola(store, posX, posY, bomb);
    
    endwin();
    
    printf("coeffient a:%f coeffient b:%f angle:%f power:%f ",store.a,store.b,store.angle,store.power);
    printf("speed : %f posX : %d posY : %d Col: %d LINE : %d mapX: %d mapY: %d",speed,posX,posY,MAP_X,MAP_Y,mposX,mposY);
    if(store.direction==1)
        printf("direction:Left \n");
    else
        printf("direction:Right \n");
    
    return 0;
}
