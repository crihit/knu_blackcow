#include <stdio.h>
#include <curses.h>
#include <termios.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <curses.h>
#include "main.h"

void get_screen(int posX,int posY){ //map배열에서 map[posY][posX]부터 스크린 전체가 꽉찰때까지 스캔
    int i,j;
    
    for(i=0;i<LINES;i++){
        for(j=0;j<COLS;j++){
            move(i,j);
            addch(map[i+posY][j+posX]);
        }
    }
}

void move_screen(int command,int *posX,int *posY){//ikjl 상하좌우로 스크린 이동
    if(command=='i'&&*posY>0)
        (*posY)--;
    if(command=='j'&&*posX>0)
        (*posX)--;
    if(command=='l'&&100-*posX>COLS)
        (*posX)++;
    if(command=='k'&&70-*posY>LINES)
        (*posY)++;
    
}

void equation(element *store){//포물선 함수
    store->b=-pow(store->power,2)*cos(store->angle*PI/180.0)*sin(store->angle*PI/180.0)/Gravity;
    store->a=tan(store->angle*PI/180.0)/2/store->b;
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
            //addch(' ');   //잔상 안보이게 하기
            
            if(posX-COLS/2>0 && posX+COLS/2<100/*MAPSIZE*/){
                move_screen('l', &mposX, &mposY);
            }
            
            get_screen(mposX, mposY);
            posX++;
            
            if(posX<=0||posX>=100/*MAPSIZE*/)//화면 벗어나면 종료
                return;
            
            if(posY<pos_Y-temp){
                for(;posY<pos_Y-temp;posY++){
                    if(posY<=0||posY>=70/*MAPSIZE*/||mvinch(posY-mposY, posX-mposX)=='*')//화면 벗어나거나 땅에 닿으면 종료
                        return;
                    if(posY-LINES/2>0 && posY+LINES/2<70/*MAPSIZE*/){
                        move_screen('k', &mposX, &mposY);
                    }
                }
            }
            else{
                for(;posY>pos_Y-temp;posY--){
                    if(posY<=0||posY>=70/*MAPSIZE*/||mvinch(posY-mposY, posX-mposX)=='*')
                        return;
                    if(posY-LINES/2>0 && posY+LINES/2<70/*MAPSIZE*/){
                        move_screen('i', &mposX, &mposY);
                    }
                }
            }
            get_screen(mposX, mposY);
            //addch(' ');
            move(posY-mposY, posX-mposX);
            if(inch()=='*')
                return;
            addch(bomb);
            //move(posY, posX);
            refresh();
            usleep(speed);
        }
    }
    else{//왼쪽발포 이하생략
        for(i=-store.b;;i--){
            
            temp=store.a*(i-store.b)*(i+store.b);
            //addch(' ');
            
            if(posX-COLS/2>0 && posX+COLS/2<100/*MAPSIZE*/){
                move_screen('j', &mposX, &mposY);
            }
            get_screen(mposX, mposY);
            posX--;
            if(posX<=0||posX>=100/*MAPSIZE*/)
                return;
            if(posY<pos_Y-temp){
                for(;posY<pos_Y-temp;posY++){
                    if(posY<=0||posY>=70/*MAPSIZE*/||mvinch(posY-mposY, posX-mposX)=='*')
                        return;
                    if(posY-LINES/2>0 && posY+LINES/2<70/*MAPSIZE*/){
                        move_screen('k', &mposX, &mposY);
                    }
                }
            }
            else{
                for(;posY>pos_Y-temp;posY--){
                    if(posY<=0||posY>=70/*MAPSIZE*/||mvinch(posY-mposY, posX-mposX)=='*')
                        return;
                    if(posY-LINES/2>0 && posY+LINES/2<70/*MAPSIZE*/){
                        move_screen('i', &mposX, &mposY);
                    }
                }
            }
            
            get_screen(mposX, mposY);
            move(posY-mposY, posX-mposX);
            if(inch()=='*')
                return;
            addch(bomb);
            //move(posY, posX);
            refresh();
            usleep(speed);
        }
        
    }
}