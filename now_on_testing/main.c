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
    if(posY+MAP_Y/2>=msizeY)
        mposY=msizeY-MAP_Y;
    else if(posY-MAP_Y/2<0)
        mposY=0;
    else
        mposY=posY-MAP_Y/2;
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
    char *buffer;
    int posX, posY;
    float speed;
    element store;
    int i,j;
    char c;
    FILE *fp;
    
    store.angle=45,store.power=30;
    /*printf("input angle power direction(Left:1,Right:0) : ");
    scanf("%f %f %d",&store.angle,&store.power,&store.direction);
    
    if(store.angle>=90){
        store.angle=89.0;
    }*/
    
    if((fp=fopen("map5.txt", "r"))==NULL){
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
    
    /*speed=40000-store.power*1000*pow(cos(store.angle*PI/180.0),2);
    
    if(speed<=24000)
        speed=24000;*/
    
    initscr();
    init_keyboard();
    set_nodelay_mode();
    clear();
    
    make_edge();
    /*if(store.direction==0)
    {
        posX = p1[1];
        posY = p1[0];
    }
    else*/
    {
        posX = p2[1];
        posY = p2[0];
    }
    move(posY, posX);
    
    /*while(map[posY][posX]==' '){
        posY++;
    }
    
    while(map[posY][posX]=='#'){
        posY--;
    }
    */
    store.direction=1;

    while(1){
        set_mpos(posX, posY);
        move_char(&posX,&posY,&store.direction);//while()문
        set_angle_power(posX, posY, &store);//while()문
        equation(&store);
        parabola(store, posX, posY-1, bomb);
        fgets(buffer, 100, stdin);
    }
    endwin();
    
    return 0;
}
