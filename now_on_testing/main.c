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
char mapname[5][20] = {"map.txt","map3.txt","map5.txt"};


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
    int mapNum;
    char buffer[100];
    element store1,store2;
    character char1,char2;
    
    int i,j;
    char c;
    FILE *fp;
    
    store1.angle=store2.angle=45;
    store1.power=store2.power=30;
    store1.direction=0,store2.direction=1;
    
    printf("select map (1,2,3) : ");
    scanf("%d",&mapNum);
    if((fp=fopen(mapname[mapNum-1], "r"))==NULL){
        printf("cannot find %s\n",mapname[mapNum-1]);
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
    
    char1.posX = p1[1];
    char1.posY = p1[0];
    
    char1.hp=3;
    char1.gas=30;
    
    char2.posX = p2[1];
    char2.posY = p2[0];
    
    char2.hp=3;
    char2.gas=30;
    
    move(char1.posY, char1.posX);
    
    /*set_mpos(char1.posX, char1.posY);
    if_descent(3, 2, &char1.posX, &char1.posY);
    set_mpos(char2.posX, char2.posY);
    if_descent(3, 2, &char2.posX, &char2.posY);
    sleep(50000);*/
    
    add_rectangle(3, 2,char1.posX,char1.posY,'o');
    add_rectangle(3, 2,char2.posX,char2.posY,'o');
    
    while(1){
        set_mpos(char1.posX, char1.posY);
        move_char(&char1.posX,&char1.posY,&store1.direction,&char1);//while()문
        set_angle_power(char1.posX, char1.posY, &store1);//while()문
        equation(&store1);
        parabola(store1, char1.posX, char1.posY-1, bomb,&char1,&char2);
        set_mpos(char1.posX, char1.posY);
        if_descent(3, 2, &char1.posX, &char1.posY);
        char1.gas=30;
        if(char1.hp<=0){
            endwin();
            return 0;
        }
        scanf("%s",buffer);
        
        set_mpos(char2.posX, char2.posY);
        move_char(&char2.posX,&char2.posY,&store2.direction,&char2);//while()문
        set_angle_power(char2.posX, char2.posY, &store2);//while()문
        equation(&store2);
        parabola(store2, char2.posX, char2.posY-1, bomb,&char2,&char1);
        set_mpos(char2.posX, char2.posY);
        if_descent(3, 2, &char2.posX, &char2.posY);
        char2.gas=30;
        if(char2.hp<=0){
            endwin();
            return 0;
        }
        scanf("%s",buffer);
        
    }
    endwin();
    
    return 0;
}
