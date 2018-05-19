#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <curses.h>
#include <sys/time.h>
#include <stdlib.h>
#define MAP_X 120
#define MAP_Y 40
struct termios new_settings,initial_settings;

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

void get_screen(char **map,int posX,int posY,int xSize, int ySize){
    int i,j;
    
    for(i=1;i<=MAP_Y;i++){
        for(j=1;j<=MAP_X;j++){
            move(i,j);
            if(i+posY>ySize||j+posX>xSize)
                addch(' ');
            else
                addch(map[i+posY-1][j+posX]);

        }
    }
    refresh();
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

int main(void){
    int command,i,j;
    int posX=0,posY=0;
    char c;
    char name[20];
    FILE *fp;
    int xSize, ySize;
    char **map;
    int p1[2], p2[2];
    
    printf("Input map name : ");
    scanf("%s",name);
    fp = fopen(name,"r");
    fscanf(fp,"%d %d",&xSize,&ySize);
    map = (char **)malloc(sizeof(int *)*(ySize+1));
    for(i=0;i<ySize+1;i++)
    {
        map[i] = (char *)malloc(sizeof(int)*(xSize+1));
    }
    for(i=0;i<ySize;i++)
    {
        for(j=0;j<xSize+1;j++)
        {
            c = fgetc(fp);
            if(c == '#')
            {
                map[i][j] = c;
            }
            else if(c == '1')
            {
                p1[0] = i;
                p1[1] = j;
                map[i][j] = ' ';
            }
            else if(c == '2')
            {
                p2[0] = i;
                p2[1] = j;
                map[i][j] = ' ';
            }
            else if(c == ' ')
            {
                map[i][j] = c;
            }
        }
    }
    for(i=0;i<ySize;i++)
    {
        for(j=0;j<xSize+1;j++)
        {
            printf("%c",map[i][j]);
        }
        printf("\n");
    }
    printf("P1 X:%d, Y:%d\nP2 X:%d, Y:%d\n",p1[1],p1[0],p2[1],p2[0]);
    sleep(5);
    initscr();
    init_keyboard();
    set_nodelay_mode();
    move(0,0);
    for(i=0;i<=MAP_X+1;i++)
    {
        move(0,i);
        addch('&');
    }
    for(i=1;i<=MAP_Y;i++)
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
    refresh();
    
    while (1) {
        if((command=get_ok_char())!=EOF){
            if(command=='a')
                break;
            move_screen(command, &posX, &posY, xSize, ySize);
        }
        get_screen(map,posX,posY,xSize,ySize);
    }
    
    
    endwin();
    
}
