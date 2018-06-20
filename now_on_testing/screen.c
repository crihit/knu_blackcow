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
            {
                if(map[i+posY-1][j+posX-1] == 'R')
                {
                    //if(turn == 0)
                    //{
                        attron(COLOR_PAIR(1));
                        addch(' ');
                        attroff(COLOR_PAIR(1));
                    //}
                    /*else
                    {
                        attron(COLOR_PAIR(charColor2));
                        addch(' ');
                        attroff(COLOR_PAIR(charColor2));
                    }*/
                }
                else if(map[i+posY-1][j+posX-1] == 'G')
                {
                    attron(COLOR_PAIR(2));
                    addch(' ');
                    attroff(COLOR_PAIR(2));
                    
                }
                else if(map[i+posY-1][j+posX-1] == 'Y')
                {
                    attron(COLOR_PAIR(3));
                    addch(' ');
                    attroff(COLOR_PAIR(3));
                    
                }
                else if(map[i+posY-1][j+posX-1] == 'B')
                {
                    attron(COLOR_PAIR(4));
                    addch(' ');
                    attroff(COLOR_PAIR(4));
                    
                }
                else if(map[i+posY-1][j+posX-1] == 'M')
                {
                    attron(COLOR_PAIR(5));
                    addch(' ');
                    attroff(COLOR_PAIR(5));
                    
                }
                else if(map[i+posY-1][j+posX-1] == 'C')
                {
                    attron(COLOR_PAIR(6));
                    addch(' ');
                    attroff(COLOR_PAIR(6));
                    
                }
                else if(map[i+posY-1][j+posX-1] == '#')
                {
                    attron(COLOR_PAIR(7));
                    addch(' ');
                    attroff(COLOR_PAIR(7));
                    
                }
                else
                {
                    addch(map[i+posY-1][j+posX-1]);
                }
            }
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

void moving_map(character char0){
    char command;
    while(1){
        get_screen(mposX, mposY, msizeX, msizeY);
        if((command=get_ok_char())!=EOF){
            if(command=='a'){
                set_mpos(char0.posX, char0.posY);
                break;
            }
            if(char0.posX-MAP_X/2>0 && char0.posX+MAP_X/2<msizeX&&char0.posY-MAP_Y/2>0&&char0.posY+MAP_Y/2&&(command=='i'||command=='k')){
                move_screen(command, &mposX, &mposY,msizeX,msizeY);
                move_screen(command, &mposX, &mposY,msizeX,msizeY);
            }
            if(char0.posX-MAP_X/2>0 && char0.posX+MAP_X/2<msizeX&&char0.posY-MAP_Y/2>0&&char0.posY+MAP_Y/2&&(command=='j'||command=='l')){
                move_screen(command, &mposX, &mposY,msizeX,msizeY);
                move_screen(command, &mposX, &mposY,msizeX,msizeY);
                move_screen(command, &mposX, &mposY,msizeX,msizeY);
            }
        }
        refresh();
    }
}

void make_char_option(character char0){
    int i,j;
    move(MAP_Y+2, 4);
    addstr("health point : ");
    for(i=0;i<char0.hp;i++)
        addch('0');
    for(;i<10;i++){
        addch(' ');
    }
    
    move(MAP_Y+2,40);
    addstr("range : ");
    for(i=0;i<char0.range;i++){
        addch('*');
    }
    for(;i<50;i++){
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
    
    for(j=0;j<4;j++){
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
        attron(COLOR_PAIR(6));
        addch(' ');
        attroff(COLOR_PAIR(6));
    }
    for(i=1;i<=MAP_Y+10;i++)
    {
        move(i,0);
        attron(COLOR_PAIR(6));
        addch(' ');
        attroff(COLOR_PAIR(6));
        move(i,MAP_X+1);
        attron(COLOR_PAIR(6));
        addch(' ');
        attroff(COLOR_PAIR(6));
    }
    move(MAP_Y+1,0);
    
    for(i=0;i<=MAP_X+1;i++)
    {
        move(MAP_Y+1,i);
        attron(COLOR_PAIR(6));
        addch(' ');
        attroff(COLOR_PAIR(6));
    }
    
    move(MAP_Y+11,0);
    
    for(i=0;i<=MAP_X+1;i++)
    {
        move(MAP_Y+11,i);
        attron(COLOR_PAIR(6));
        addch(' ');
        attroff(COLOR_PAIR(6));
    }
}
