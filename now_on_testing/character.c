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
