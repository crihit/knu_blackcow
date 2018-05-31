#include <stdio.h>
#include <curses.h>
#include <termios.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <curses.h>
#include "main.h"



void equation(element *store){//포물선 함수
    store->b=-pow(store->power,2)*cos(store->angle*PI/180.0)*sin(store->angle*PI/180.0)/Gravity;
    store->a=tan(store->angle*PI/180.0)/2/store->b;
}

void erase_map(int posX, int posY,character *char0,character *char1){
    if(char0->range==0&&char0->power==0){
        add_rectangle(3, 2, char0->posX, char0->posY, ' ');
        char0->posX=posX;
        char0->posY=posY-1;
        add_rectangle(3, 2, char0->posX, char0->posY, 'o');
        return;
    }
        
    int i,j,k,range=char0->range;
    for(k=0;k<range;k++){
        for(i = posY-k; i <= posY+k; i++){
            for(j = posX - k; j<= posX+k; j++){
                if(i<=0||i>=msizeY||j<0||j>=msizeX-1)
                    break;
                if(pow((i-posY)*2,2)+pow(j-posX, 2)>pow(k, 2))
                    continue;
                map[i][j] = '@';
            }
        }
        for(i = posY-(k-1); i <= posY+(k-1); i++){
            for(j = posX - (k-1); j<= posX+(k-1); j++){
                if(i<=0||i>=msizeY||j<0||j>=msizeX-1)
                    break;
                if(pow((i-posY)*2,2)+pow(j-posX, 2)>pow(k-1, 2))
                    continue;
                map[i][j] = ' ';
            }
        }
        get_screen(mposX, mposY, msizeX, msizeY);
        refresh();
        usleep(100000);
    }
    for(i = posY-k; i <= posY+k; i++){
        for(j = posX - k; j<= posX+k; j++){
            if(i<=0||i>=msizeY||j<0||j>=msizeX-1)
                break;
            if(pow((i-posY)*2,2)+pow(j-posX, 2)>pow(range, 2))
                continue;
            else if(i==char0->posY&&j==char0->posX){
                char0->hp-=char0->power;
            }
            else if(i==char1->posY&&j==char1->posX){
                char1->hp-=char0->power;
            }
            map[i][j] = ' ';
        }
    }
    get_screen(mposX, mposY, msizeX, msizeY);
    refresh();
    sleep(1);
    return;
}


void parabola(element store,int pos_X,int pos_Y,char bomb,character *char0,character *char1){
    //mposX=5;
    int posX=pos_X,posY=pos_Y;//map[i][j]에서의 posY,posX값
    int i,temp,speed;
    
    speed=40000-store.power*1000*pow(cos(store.angle*PI/180.0),2);
    
    if(speed<=24000)//최대속도
        speed=24000;
    
    if(store.direction==0){//오른쪽 발포
        for(i=store.b;;i++){
            
            temp=store.a*(i-store.b)*(i+store.b);//포물선 높이
            
            if(posX-MAP_X/2>0 && posX+MAP_X/2<msizeX){
                move_screen('l', &mposX, &mposY,msizeX,msizeY);
            }
            
            get_screen(mposX, mposY,msizeX,msizeY);
            posX++;
            
            if(posX<=1||posX>=msizeX-1)//화면 벗어나면 종료
                return;
            
            if(posY<pos_Y-temp){
                for(;posY<pos_Y-temp;posY++){
                    if(posY<=1||posY>=msizeY-1)//화면 벗어나거나 땅에 닿으면 종료
                        return;
                    if(map[posY][posX]=='#'||map[posY][posX]=='o'){
                        erase_map(posX,posY,char0,char1);
                        return;
                    }
                    if(posY-MAP_Y/2>=0 && posY+MAP_Y/2<msizeY-1){
                        move_screen('k', &mposX, &mposY,msizeX,msizeY);
                    }
                }
            }
            else{
                for(;posY>pos_Y-temp;posY--){
                    if(posY<=1||posY>=msizeY-1)
                        return;
                    if(map[posY][posX]=='#'||map[posY][posX]=='o'){
                        erase_map(posX,posY,char0,char1);
                        return;
                    }
                    if(posY-MAP_Y/2>=0 && posY+MAP_Y/2<msizeY-1){
                        move_screen('i', &mposX, &mposY,msizeX,msizeY);
                    }
                }
            }
            get_screen(mposX, mposY,msizeX,msizeY);
            move(posY-mposY, posX-mposX);
            if(map[posY][posX]=='#'){
                erase_map(posX,posY,char0,char1);
                return;
            }
            addch(bomb);
            refresh();
            usleep(speed);
        }
    }
    else{//왼쪽발포 이하생략
        for(i=-store.b;;i--){
            
            temp=store.a*(i-store.b)*(i+store.b);
            
            if(posX-MAP_X/2>0 && posX+MAP_X/2<msizeX){
                move_screen('j', &mposX, &mposY,msizeX,msizeY);
            }
            get_screen(mposX, mposY,msizeX,msizeY);
            posX--;
            if(posX<=1||posX>=msizeX-1)
                return;
            if(posY<pos_Y-temp){
                for(;posY<pos_Y-temp&&posY;posY++){
                    if(posY<=1||posY>=msizeY-1)
                        return;
                    if(map[posY][posX]=='#'||map[posY][posX]=='o'){
                        erase_map(posX,posY,char0,char1);
                        return;
                    }
                    if(posY-MAP_Y/2>=0 && posY+MAP_Y/2<msizeY-1){
                        move_screen('k', &mposX, &mposY,msizeX,msizeY);
                    }
                }
            }
            else{
                for(;posY>pos_Y-temp;posY--){
                    if(posY<=1||posY>=msizeY-1)
                        return;
                    if(map[posY][posX]=='#'||map[posY][posX]=='o'){
                        erase_map(posX,posY,char0,char1);
                        return;
                    }

                    if(posY-MAP_Y/2>=0 && posY+MAP_Y/2<msizeY-1){
                        move_screen('i', &mposX, &mposY,msizeX,msizeY);
                    }
                }
            }
            
            get_screen(mposX, mposY,msizeX,msizeY);
            move(posY-mposY, posX-mposX);
            if(map[posY][posX]=='#'){
                erase_map(posX,posY,char0,char1);
                return;
            }
            addch(bomb);
            refresh();
            usleep(speed);
        }
        
    }
}
