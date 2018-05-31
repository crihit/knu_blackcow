#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <termios.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>
#include <stdlib.h>
#include "main.h"

void add_rectangle(int Xlength,int Ylength,int posX,int posY,int input){
    int i,j;
    
    for(i=0;i<Ylength;i++){
        for(j=0;j<Xlength;j++){
            move(posY-mposY+i, posX-mposX+j);
            addch(input);
        }
    }
}

int touch_rectangle(int Xlength,int Ylength,int posX,int posY,int direct){
    int i;
    if(direct==0){
        for(i=0;i<Ylength-1;i++)
        if(map[posY-1+i][posX+Xlength-1]=='#')
            return 0;
    }
    else{
        for(i=0;i<Ylength-1;i++)
        if(map[posY-1+i][posX-2]=='#')
            return 0;
    }
    return 1;
}

void if_climb(int Xlength,int Ylength,int *posX,int *posY,int direct){
    if(direct==0){
        if(map[*posY+Ylength-2][*posX+Xlength-1]=='#')
            (*posY)--;
    }
    else{
        if(map[*posY+Ylength-2][*posX-2]=='#')
            (*posY)--;
    }
    set_mpos(*posX, *posY);
}

void if_descent(int Xlength,int Ylength,int *posX,int *posY){
    int i;
    while(1){
        for(i=-1;i<=Xlength-2;i++){
            if(map[*posY+Ylength-1][*posX+i]=='#'){
                return;
            }
        }
        add_rectangle(3, 2,*posX,*posY,' ');
        (*posY)++;
        add_rectangle(3, 2,*posX,*posY,'o');
        refresh();
        usleep(50000);
        set_mpos(*posX, *posY);
        if(*posY>=msizeY){
            endwin();
            exit(1);
        }
    }
}

void move_char(int *posX, int *posY,int *direct){
    int command;
    int x,y;

    //make_edge();
    while(1){
        get_screen(mposX, mposY, msizeX, msizeY);
        getyx(curscr, y, x);
        if(y==MAP_Y+1&&x==MAP_X+1)
            continue;
        add_rectangle(3, 2,*posX,*posY,'o');
        move(*posY-mposY, *posX-mposX);
        if((command=get_ok_char())!=EOF){
            if(command=='a')
                break;

            if(command=='l'&&touch_rectangle(3,2, *posX, *posY,0)){
                if(*posX-MAP_X/2>0 && *posX+MAP_X/2<msizeX){
                    move_screen(command, &mposX, &mposY,msizeX,msizeY);
                }
                add_rectangle(3, 2,*posX,*posY,' ');
                if_climb(3, 2, posX, posY, 0);
                (*posX)++;
                if_descent(3, 2, posX, posY);
                *direct=0;
                add_rectangle(3, 2,*posX,*posY,'o');
                move(*posY-mposY, *posX-mposX);
            }
            if(command=='j'&&touch_rectangle(3,2, *posX, *posY,1)){
                if(*posX-MAP_X/2>0 && *posX+MAP_X/2<msizeX){
                    move_screen(command, &mposX, &mposY,msizeX,msizeY);
                }
                add_rectangle(3, 2,*posX,*posY,' ');
                if_climb(3, 2, posX, posY, 1);
                (*posX)--;
                if_descent(3, 2, posX, posY);
                *direct=1;
                add_rectangle(3, 2,*posX,*posY,'o');
                move(*posY-mposY, *posX-mposX);
            }
        }
        if_descent(3, 2, posX, posY);
        refresh();
    }
}

void set_angle_power(int posX,int posY,element *store){
    int command;
    char number[2];
    move(posY-mposY-2, posX-mposX);
    addstr("angle");
    while(1){
        if((command=get_ok_char())!=EOF){
            if(command=='a')
                break;
            if(command=='k'&&store->angle>1){
                (store->angle)--;
                move(posY-1-mposY, posX-mposX);
            }
            if(command=='i'&&store->angle<89){
                (store->angle)++;
            }
        }
        number[0]=store->angle/10+'0',number[1]=(int)store->angle%10+'0';
        move(posY-mposY-1, posX-mposX);
        addch(number[0]),addch(number[1]);
        refresh();
    }
    
    move(posY-mposY-2, posX-mposX);
    addstr("power");
    while(1){
        if((command=get_ok_char())!=EOF){
            if(command=='a')
                break;
            if(command=='k'&&store->power>1){
                (store->power)--;
            }
            if(command=='i'&&store->power<60){
                (store->power)++;
            }
        }
        number[0]=store->power/10+'0',number[1]=(int)store->power%10+'0';
        move(posY-mposY-1, posX-mposX);
        addch(number[0]),addch(number[1]);
        refresh();
    }

}
