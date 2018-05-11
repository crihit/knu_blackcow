//
//  main.c
//  attacked
//
//  Created by knuprime086 on 2018. 5. 10..
//  Copyright © 2018년 knuprime086. All rights reserved.
//

#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <math.h>

char map[200][200]; // 임시방편 맵
int isColl = 1; // 하늘에서 폭탄 존재 유무

typedef struct player{
    int x;
    int y;
    int hp;
}player;

int find_attack(int x, int y, player player1); // 피격되었는지 아닌지의 함수

int main(void) {
    

}

int find_attack(int x, int y,player player1){ // 캐릭터 1x1크기
    
    int attack_condition = 0;
    
    //폭탄 범위 : 1
    
    if( player1.x > x-1 && player1.x < x+1)
        if(player1.y > y-1 && player1.y && y+1){
            attack_condition = 1;
            isColl = 0; // 하늘에서 폭탄이 존재하지 않음
            return attack_condition;
        }
    
    //attack_condition이 1이면 직격
    
    if(map[player1.x][player1.y] == '*')
    {
        attack_condition = 2;
    }
    
    // attack_condition이 2이면 땅에 떨어짐
    
    return attack_condition;
}
