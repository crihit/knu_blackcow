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

character charArray[6];

void how_to_play(){
    move(32, 80);
    addch('I');
    move(35, 80);
    addch('K');
    move(35, 85);
    addch('L');
    move(35, 75);
    addch('J');
    move(36, 75);
    addstr("move");
    
    move(35, 30);
    addch('A');
    move(36, 30);
    addstr("select");
    move(35, 45);
    addch('S');
    move(36, 45);
    addstr("menu");
    move(35, 60);
    addch('D');
    move(36, 60);
    addstr("MapSearch");
    refresh();
}

void chooses_option(character *char0){
    
    char command;
    int choose=0;
    
    while(1){
        move(MAP_Y+9, 4+choose*20);
        addch('^');
        
        if((command=get_ok_char())!=EOF){
            if(command=='a'||command=='s'){
                move(MAP_Y+9, 4+choose*20);
                addch(' ');
                char0->range=char0->btype[choose].range;
                char0->power=char0->btype[choose].power;
                break;
            }
            if(command=='l'){
                move(MAP_Y+9, 4+choose*20);
                addch(' ');
                choose=(choose+1)%4;
            }
            else if(command=='j'){
                move(MAP_Y+9, 4+choose*20);
                addch(' ');
                choose=(choose-1)%4;
                if(choose<0)
                    choose=3;
            }
        }
        
        refresh();
    }
}

void chooses_map(int *mapNum){
    
    char command;
    int choose=0;
    for(choose=0;choose<3;choose++){
        move(20, 20+30*choose);
        addstr("map");
        addch(choose+'0');
        addstr(".txt");
    }
    choose=0;
    while(1){
        move(21, 20+30*choose);
        addch('^');
        
        if((command=get_ok_char())!=EOF){
            if(command=='a'){
                *mapNum=choose%3;
                break;
            }
            if(command=='l'){
                move(21, 20+30*choose);
                addch(' ');
                choose=(choose+1)%3;
            }
            else if(command=='j'){
                move(21, 20+30*choose);
                addch(' ');
                choose=(choose-1)%3;
                if(choose<0)
                    choose=2;
            }
        }
        
        refresh();
    }
}

void characterArray(){
    charArray[0].hp=7;
    charArray[0].gas=50;
    charArray[0].btype[0].power=3,charArray[0].btype[0].range=7;
    charArray[0].btype[1].power=1,charArray[0].btype[1].range=10;
    charArray[0].btype[2].power=5,charArray[0].btype[2].range=5;
    charArray[0].btype[3].power=0,charArray[0].btype[3].range=0;
    charArray[0].range=charArray[0].btype[0].range;
    charArray[0].power=charArray[0].btype[0].power;
    charArray[0].colorType = 1;
    charArray[0].color = 'R';
    
    charArray[1].hp=10;
    charArray[1].gas=30;
    charArray[1].btype[0].power=2,charArray[1].btype[0].range=8;
    charArray[1].btype[1].power=0,charArray[1].btype[1].range=13;
    charArray[1].btype[2].power=4,charArray[1].btype[2].range=6;
    charArray[1].btype[3].power=0,charArray[1].btype[3].range=0;
    charArray[1].range=charArray[1].btype[0].range;
    charArray[1].power=charArray[1].btype[0].power;
    charArray[1].colorType = 2;
    charArray[1].color = 'G';

    charArray[2].hp=20;
    charArray[2].gas=20;
    charArray[2].btype[0].power=2,charArray[2].btype[0].range=4;
    charArray[2].btype[1].power=1,charArray[2].btype[1].range=5;
    charArray[2].btype[2].power=0,charArray[2].btype[2].range=6;
    charArray[2].btype[3].power=0,charArray[2].btype[3].range=0;
    charArray[2].range=charArray[2].btype[0].range;
    charArray[2].power=charArray[2].btype[0].power;
    charArray[2].colorType = 3;
    charArray[2].color = 'Y';

    charArray[3].hp=4;
    charArray[3].gas=40;
    charArray[3].btype[0].power=5,charArray[3].btype[0].range=8;
    charArray[3].btype[1].power=2,charArray[3].btype[1].range=13;
    charArray[3].btype[2].power=7,charArray[3].btype[2].range=6;
    charArray[3].btype[3].power=0,charArray[3].btype[3].range=0;
    charArray[3].range=charArray[3].btype[0].range;
    charArray[3].power=charArray[3].btype[0].power;
    charArray[3].colorType = 4;
    charArray[3].color = 'B';

    charArray[4].hp=13;
    charArray[4].gas=30;
    charArray[4].btype[0].power=1,charArray[4].btype[0].range=8;
    charArray[4].btype[1].power=0,charArray[4].btype[1].range=11;
    charArray[4].btype[2].power=3,charArray[4].btype[2].range=6;
    charArray[4].btype[3].power=0,charArray[4].btype[3].range=0;
    charArray[4].range=charArray[4].btype[0].range;
    charArray[4].power=charArray[4].btype[0].power;
    charArray[4].colorType = 5;
    charArray[4].color = 'M';

    charArray[5].hp=10;
    charArray[5].gas=3;
    charArray[5].btype[0].power=6,charArray[5].btype[0].range=10;
    charArray[5].btype[1].power=3,charArray[5].btype[1].range=16;
    charArray[5].btype[2].power=8,charArray[5].btype[2].range=8;
    charArray[5].btype[3].power=1,charArray[5].btype[3].range=20;
    charArray[5].range=charArray[5].btype[0].range;
    charArray[5].power=charArray[5].btype[0].power;
    charArray[5].colorType = 6;
    charArray[5].color = 'C';
}

void chooses_character(character *char0){
    char command;
    int chooseX=0,chooseY=0;
    characterArray();
    while(1){
        move(15+15*chooseY, 20+30*chooseX);
        addch('^');
        
        if((command=get_ok_char())!=EOF){
            if(command=='a'){
                *char0=charArray[chooseX+chooseY*3];
                addch(' ');
                break;
            }
            if(command=='l'){
                move(15+15*chooseY, 20+30*chooseX);
                addch(' ');
                chooseX=(chooseX+1)%3;
            }
            if(command=='i'){
                move(15+15*chooseY, 20+30*chooseX);
                addch(' ');
                chooseY=(chooseY-1)%2;
                if(chooseY<0)
                    chooseY=1;
            }
            if(command=='k'){
                move(15+15*chooseY, 20+30*chooseX);
                addch(' ');
                chooseY=(chooseY+1)%2;

            }
            if(command=='j'){
                move(15+15*chooseY, 20+30*chooseX);
                addch(' ');
                chooseX=(chooseX-1)%3;
                if(chooseX<0)
                    chooseX=2;
            }
        }
        
        refresh();
    }
}

void print_character(){
    int i,j,k,l,number[2];
    characterArray();
    for(k=0;k<2;k++)
        for(j=0;j<3;j++){
            move(10+15*k-5, 20+30*j);
            addstr("character");
            addch(j+'1');
            
            move(10+15*k-4, 20+30*j);
            addstr("health point : ");
            number[0]=charArray[j+3*k].hp/10+'0',number[1]=(int)charArray[j+3*k].hp%10+'0';
            addch(number[0]),addch(number[1]);

            
            move(10+15*k-3, 20+30*j);
            addstr("gas : ");
            number[0]=charArray[j+3*k].gas/10+'0',number[1]=(int)charArray[j+3*k].gas%10+'0';
            addch(number[0]),addch(number[1]);

            for(l=0;l<3;l++){
                move(10+15*k-2+2*l, 20+30*j);
                addstr("range : ");
                for(i=0;i<charArray[j+3*k].btype[l].range;i++){
                    addch('*');
                }
                for(;i<5;i++){
                    addch(' ');
                }
                move(10+15*k-1+2*l, 20+30*j);
                addstr("power : ");
                for(i=0;i<charArray[j+3*k].btype[l].power;i++){
                    addch('+');
                }
                for(;i<5;i++){
                    addch(' ');
                }
            }
    }
    refresh();
}
