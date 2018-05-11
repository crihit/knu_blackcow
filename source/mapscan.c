#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <curses.h>
#include <sys/time.h>
#include <stdlib.h>

struct termios new_settings,initial_settings;

int map[1000][1000];

void set_nodelay_mode(){
    int termflags;
    termflags=fcntl(0,F_GETFL);
    termflags |=O_NDELAY;
    fcntl(0, F_SETFL,termflags);
}

int get_ok_char(){
    int c;
    while((c=getchar())!=EOF&&strchr("jklia",c)==NULL);
    return c;
}

void init_keyboard()
{
    tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}

void get_screen(int posX,int posY){
    int i,j;
    
    for(i=0;i<LINES;i++){
        for(j=0;j<COLS;j++){
            move(i,j);
            addch(map[i+posY][j+posX]);
        }
    }
    refresh();
}

void move_screen(int command,int *posX,int *posY){
    if(command=='i'&&*posY>0)
        (*posY)--;
    if(command=='j'&&*posX>0)
        (*posX)--;
    if(command=='l'&&100-*posX>COLS)
        (*posX)++;
    if(command=='k'&&70-*posY>LINES)
        (*posY)++;
    
}

int main(void){
    int command,i,j,k;
    int posX=0,posY=0;
    char c;
    FILE *fp;
    

    
    initscr();
    init_keyboard();
    set_nodelay_mode();
    
    if((fp=fopen("map3.bin", "rb"))==NULL){
        printf("cannot find map.txt");
        exit(1);
    }
    
    for(k=0;k<7;k++)
    for(i=0;i<10;i++){
        for(j=0;j<100;j++){
            fread(&c,sizeof(char),1,fp);
            map[i+k*10][j]=c;
        }
        fread(&c, sizeof(char), 1, fp);
    }
    
    
    while (1) {
        if((command=get_ok_char())!=EOF){
            if(command=='a')
                break;
            move_screen(command, &posX, &posY);
        }
        get_screen(posX,posY);
    }
    
    
    endwin();
    
}
