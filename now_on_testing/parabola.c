#include <stdio.h>
#include <curses.h>
#include <termios.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <curses.h>
#include "main.h"

/*void get_screen(int posX,int posY){ //map배열에서 map[posY][posX]부터 스크린 전체가 꽉찰때까지 스캔
 int i,j;
 
 for(i=0;i<LINES;i++){
 for(j=0;j<COLS;j++){
 move(i,j);
 if(i+posY>=msizeY||j+posX>=msizeX||i+posY<0||j+posX<0)//오류수정
 addch(' ');
 else{
 addch(map[i+posY][j+posX]);
 }
 }
 }
 }*/

void get_screen(int posX,int posY,int xSize, int ySize){
    int i,j;
    
    for(i=1;i<=MAP_Y;i++){
        for(j=1;j<=MAP_X;j++){
            move(i,j);
            if(i+posY>ySize||j+posX>xSize)
                addch(' ');
            else
                addch(map[i+posY-1][j+posX-1]);
            
        }
    }
}

/*void move_screen(int command,int *posX,int *posY){//ikjl 상하좌우로 스크린 이동
 if(command=='i'&&*posY>0)
 (*posY)--;
 if(command=='j'&&*posX>0)
 (*posX)--;
 if(command=='l'&&msizeX-*posX>COLS)
 (*posX)++;
 if(command=='k'&&msizeY-*posY>LINES)
 (*posY)++;
 
 }*/

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


void equation(element *store){//포물선 함수
    store->b=-pow(store->power,2)*cos(store->angle*PI/180.0)*sin(store->angle*PI/180.0)/Gravity;
    store->a=tan(store->angle*PI/180.0)/2/store->b;
}

void erase_map(int posX, int posY){
    
    int i,j,k;
    for(k=0;k<10;k++){
        for(i = posY-k; i <= posY+k; i++){
            for(j = posX - k; j<= posX+k; j++){
                map[i][j] = '@';
            }
        }
        for(i = posY-(k-1); i <= posY+(k-1); i++){
            for(j = posX - (k-1); j<= posX+(k-1); j++)
                map[i][j] = ' ';
        }
        get_screen(mposX, mposY, msizeX, msizeY);
        refresh();
        usleep(100000);
    }
    for(i = posY-k; i <= posY+k; i++){
        for(j = posX - k; j<= posX+k; j++)
            map[i][j] = ' ';
    }
    get_screen(mposX, mposY, msizeX, msizeY);
    refresh();
    sleep(1);
    return;
}


void parabola(element store,int pos_X,int pos_Y,char bomb){
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
            
            if(posX<=0||posX>=msizeX)//화면 벗어나면 종료
                return;
            
            if(posY<pos_Y-temp){
                for(;posY<pos_Y-temp;posY++){
                    if(posY<=0||posY>=msizeY)//화면 벗어나거나 땅에 닿으면 종료
                        return;
                    if(map[posY][posX]=='#'){
                        erase_map(posX,posY);
                        return;
                    }
                    if(posY-MAP_Y/2>0 && posY+MAP_Y/2<msizeY){
                        move_screen('k', &mposX, &mposY,msizeX,msizeY);
                    }
                }
            }
            else{
                for(;posY>pos_Y-temp;posY--){
                    if(posY<=0||posY>=msizeY)
                        return;
                    if(map[posY][posX]=='#'){
                        erase_map(posX,posY);
                        return;
                    }
                    if(posY-MAP_Y/2>0 && posY+MAP_Y/2<msizeY){
                        move_screen('i', &mposX, &mposY,msizeX,msizeY);
                    }
                }
            }
            get_screen(mposX, mposY,msizeX,msizeY);
            move(posY-mposY, posX-mposX);
            if(map[posY][posX]=='#'){
                erase_map(posX,posY);
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
            if(posX<=0||posX>=msizeX)
                return;
            if(posY<pos_Y-temp){
                for(;posY<pos_Y-temp;posY++){
                    if(posY<=1||posY>=msizeY)
                        return;
                    if(map[posY][posX]=='#'){
                        erase_map(posX,posY);
                        return;
                    }
                    if(posY-MAP_Y/2>0 && posY+MAP_Y/2<msizeY){
                        move_screen('k', &mposX, &mposY,msizeX,msizeY);
                    }
                }
            }
            else{
                for(;posY>pos_Y-temp;posY--){
                    if(posY<=1||posY>=msizeY||map[posY][posX]=='#')
                        return;
                    if(posY-MAP_Y/2>0 && posY+MAP_Y/2<msizeY){
                        move_screen('i', &mposX, &mposY,msizeX,msizeY);
                    }
                }
            }
            
            get_screen(mposX, mposY,msizeX,msizeY);
            move(posY-mposY, posX-mposX);
            if(map[posY][posX]=='#'){
                erase_map(posX,posY);
                return;
            }
            addch(bomb);
            refresh();
            usleep(speed);
        }
        
    }
}
