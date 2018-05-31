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
character char1,char2;

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
    element store1,store2;

    int i,j;
    char c;
    FILE *fp;
    
    store1.angle=store2.angle=45;
    store1.power=store2.power=30;
    store1.direction=0,store2.direction=1;
    
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

    char1.posX = p1[1];
    char1.posY = p1[0]-40;
    
    char1.hp=3;
    char1.gas=10;

    char2.posX = p2[1];
    char2.posY = p2[0];
    
    char2.hp=3;
    char2.hp=10;
    
    move(char1.posY, char2.posX);
    
    /*while(map[posY][posX]==' '){
        posY++;
    }
    
    while(map[posY][posX]=='#'){
        posY--;
    }
    */
    set_mpos(char1.posX, char1.posY);
    if_descent(3, 2, &char1.posX, &char1.posY);
    set_mpos(char2.posX, char2.posY);
    if_descent(3, 2, &char2.posX, &char2.posY);
    sleep(50000);

    
    while(1){
        set_mpos(char1.posX, char1.posY);
        move_char(&char1.posX,&char1.posY,&store1.direction,char1);//while()문
        set_angle_power(char1.posX, char1.posY, &store1);//while()문
        equation(&store1);
        parabola(store1, char1.posX, char1.posY-1, bomb);
        set_mpos(char1.posX, char1.posY);
        if_descent(3, 2, &char1.posX, &char1.posY);
        fgets(buffer, 100, stdin);
        
        set_mpos(char2.posX, char2.posY);
        move_char(&char2.posX,&char2.posY,&store2.direction,char2);//while()문
        set_angle_power(char2.posX, char2.posY, &store2);//while()문
        equation(&store2);
        parabola(store2, char2.posX, char2.posY-1, bomb);
        set_mpos(char2.posX, char2.posY);
        if_descent(3, 2, &char2.posX, &char2.posY);
        fgets(buffer, 100, stdin);

    }
    endwin();
    
    return 0;
}
