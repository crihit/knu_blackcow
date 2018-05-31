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

void get_screen(int posX,int posY,int xSize, int ySize){
    int i,j=1;
    
    for(i=1;i<=MAP_Y;i++){
        for(j=1;j<=MAP_X;j++){
            move(i,j);
            if(i+posY>ySize||j+posX>xSize)
                addch(' ');
            else
                addch(map[i+posY-1][j+posX-1]);
        }
    }
    /*if(i==MAP_Y+1&&j==MAP_X+1)
     return 1;
     return 0;*/
}

void move_screen(int command,int *posX,int *posY, int mapX, int mapY){
    if(command=='i'&&*posY>0)
        (*posY)--;
    if(command=='j'&&*posX>0)
        (*posX)--;
    if(command=='l'&&(*posX+mapX)>MAP_X&&(mapX-*posX)>MAP_X)
        (*posX)++;
    if(command=='k'&&(*posY+mapY)>MAP_Y&&(mapY-*posY)>MAP_Y)
        (*posY)++;
    
}


void make_edge(){
    int i;
    move(0,0);
    for(i=0;i<=MAP_X+1;i++)
    {
        move(0,i);
        addch('&');
    }
    for(i=1;i<=MAP_Y+10;i++)
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
    
    move(MAP_Y+11,0);
    
    for(i=0;i<=MAP_X+1;i++)
    {
        move(MAP_Y+11,i);
        addch('&');
    }
    
}
