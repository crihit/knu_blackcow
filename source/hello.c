#include <stdio.h>
#include <curses.h>
#include <unistd.h>

int main()
{
    int i;
    char bomb = '*';
    char blank= ' ';
    int arr[31][2];
    int posX, posY;
    float temp = 0;
    initscr();
    clear();
    posX = COLS-70;
    posY = LINES-5;
    for(i=0;i<30;i++)
    {
        move(posY,posX);
        addch(bomb);
        move(LINES - 1, COLS -1);
        refresh();
        usleep(500000);
        move(posY,posX);
        addch(blank);
        
        temp = 0-(((float)i/2)-7.5)*(((float)i/2)-7.5);
        temp *= 0.3;
        posX=COLS-70+i;
        posY=LINES-5+(int)temp;
        arr[i][0] = posX;
        arr[i][1] = posY;
    }
    endwin();
//    for(i=1;i<30;i++)
//    {
//        temp = 0-(((float)i/2)-7.5)*(((float)i/2)-7.5);
//        temp *= 0.8;
//        printf("%d ",(int)temp);
//        posX+=i;
//        posY+=(int)temp;
//        printf("%d %d\n",posX,posY);
//
//    }
//    for(i=0;i<30;i++)
//    {
//        printf("%d %d\n",arr[i][0],arr[i][1]);
//    }
    
    return 0;
}
