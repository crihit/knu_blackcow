#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <math.h>
#define PI 3.1415926535
#define Gravity 10

struct coeffient{
    float angle;
    float power;
    float a;
    float b;
};

typedef struct coeffient element;

void equation(element *store){
    store->b=-store->power;
    store->a=tan(store->angle*PI/180.0)/2/store->b;
}


void parabola(element store,int pos_X,int pos_Y,char bomb){
    int posX=pos_X,posY=pos_Y,i,temp;
    int lateX, lateY;
    for(i=store.b;i<=-store.b;i++){
        
        temp=store.a*(i-store.b)*(i+store.b);
        //temp*=0.3;
        posX++;
        posY=pos_Y-temp;
        //addch(' ');
        move(posY, posX);
        addch(bomb);
        //move(posY, posX);
        move(LINES-1,COLS-1);
        refresh();
        move(posY, posX);
        addch(' ');
        move(posY, posX);
        usleep(30000-store.power*500+10000*sqrt(temp));
    }
}

int main(void)
{
    char bomb = '*';
    
    int posX, posY;
    element store;
    
    printf("Input angle and power : ");
    scanf("%f %f",&store.angle,&store.power);
    initscr();
    clear();
    posX = 5;
    posY = LINES-5;
    
    /*for(i=0;i<30;i++)
     {
     move(posY,posX);
     addch(bomb);
     move(LINES - 1, COLS -1);
     refresh();
     usleep(300000);
     move(posY,posX);
     addch(blank);
     
     temp = 53-(((float)i/2)-7.5)*(((float)i/2)-7.5);
     temp *= 0.3;
     posX=COLS-70+i;
     posY=LINES-5-(int)temp;
     }*/
    
    equation(&store);
    
    move(posY, posX);
    
    parabola(store, posX, posY, bomb);
    endwin();
    return 0;
}

