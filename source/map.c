#include <stdio.h>
#include <stdlib.h>
#define MAP_X 60
#define MAP_Y 20

int main()
{
    FILE *fp;
    int i,j;
    char c;
    char map[MAP_Y+1][MAP_X+1];
    int p1[2], p2[2];
    fp = fopen("map.txt","r");
    for(i=0;i<MAP_Y;i++)
    {
        for(j=0;j<MAP_X+1;j++)
        {
            c = fgetc(fp);
            if(c == '#')
            {
                map[i][j] = c;
            }
            else if(c == '1')
            {
                p1[0] = i;
                p2[1] = j;
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
    
    for(i=0;i<MAP_Y;i++)
    {
        for(j=0;j<MAP_X;j++)
        {
            printf("%c",map[i][j]);
        }
        printf("\n");
    }
    printf("P1 X:%d, Y:%d\nP2 X:%d, Y:%d\n",p1[1],p1[0],p2[1],p2[0]);
    return 0;
}
