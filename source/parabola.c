#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <termios.h>
#include <math.h>
#define PI 3.1415926535
#define Gravity 9.8

struct coeffient{
    float angle;
    float power;
    float a;
    float b;
    int direction;
};

typedef struct coeffient element;

void equation(element *store){
    store->b=-pow(store->power,2)*cos(store->angle*PI/180.0)*sin(store->angle*PI/180.0)/Gravity;
    store->a=tan(store->angle*PI/180.0)/2/store->b;
}


void parabola(element store,int pos_X,int pos_Y,char bomb){
    int posX=pos_X,posY=pos_Y,i,temp;
    
    if(store.direction==0){
        for(i=store.b;i<=-store.b;i++){
            
            temp=store.a*(i-store.b)*(i+store.b);
            //temp*=0.7;
            posX++;
            if(posX<=0||posX>=COLS)
                break;
            posY=pos_Y-temp;
            if(posY<=0||posY>=LINES)
                break;
            //addch(' ');
            move(posY, posX);
            addch(bomb);
            move(posY, posX);
            refresh();
            usleep(40000-store.power*1000*pow(cos(store.angle*PI/180.0),2));
        }
    }
    else{
        for(i=-store.b;i>=store.b;i--){
            
            temp=store.a*(i-store.b)*(i+store.b);
            //temp*=0.7;
            posX--;
            if(posX<=0||posX>=COLS)
                break;
            posY=pos_Y-temp;
            if(posY<=0||posY>=LINES)
                break;
            //addch(' ');
            move(posY, posX);
            addch(bomb);
            move(posY, posX);
            refresh();
            usleep(40000-store.power*1000*pow(cos(store.angle*PI/180.0),2));
        }
        
    }
    sleep(1);
}

int main(void)
{
    char bomb = '*';
    
    int posX, posY;
    element store;
    
    printf("input angle power direction(Left:1,Right:0) : ");
    scanf("%f %f %d",&store.angle,&store.power,&store.direction);
    
    initscr();
    clear();
    if(store.direction==0)
        posX = 5;
    else
        posX = COLS-5;
    posY = LINES-5;
    
    
    if(store.power>60)
        store.power=60;
    
    equation(&store);
    
    move(posY, posX);
    
    parabola(store, posX, posY, bomb);
    
    endwin();
    
    printf("coeffient a:%f coeffient b:%f angle:%f power:%f ",store.a,store.b,store.angle,store.power);
    printf("speed : %f ",40000-store.power*500*cos(store.angle*PI/180.0));
    if(store.direction==1)
        printf("direction:Left \n");
    else
        printf("direction:Right \n");
    
    return 0;
}

