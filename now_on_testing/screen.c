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

void make_char_option(character char0){
    int i,j;
    move(MAP_Y+2, 4);
    addstr("health point : ");
    for(i=0;i<char0.hp;i++)
        addch('0');
    for(;i<3;i++){
        addch(' ');
    }
    
    move(MAP_Y+2,40);
    addstr("range : ");
    for(i=0;i<char0.range;i++){
        addch('*');
    }
    for(;i<30;i++){
        addch(' ');
    }

    move(MAP_Y+4, 4);
    addstr("gas : ");
    for(i=0;i<char0.gas;i++){
        addch('>');
    }
    for(;i<30;i++){
        addch(' ');
    }
    
    move(MAP_Y+4, 40);
    addstr("power : ");
    for(i=0;i<char0.power;i++){
        addch('+');
    }
    for(;i<30;i++){
        addch(' ');
    }
    
    for(j=0;j<3;j++){
        move(MAP_Y+6, 4+j*20);
        addstr("type");
        addch(j+'1');
        move(MAP_Y+7, 4+j*20);
        addstr("range : ");
        for(i=0;i<char0.btype[j].range;i++){
            addch('*');
        }
        for(;i<5;i++){
            addch(' ');
        }
        move(MAP_Y+8, 4+j*20);
        addstr("power : ");
        for(i=0;i<char0.btype[j].power;i++){
            addch('+');
        }
        for(;i<5;i++){
            addch(' ');
        }


    }
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
