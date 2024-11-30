#pragma once
#include "value.h"
#include "judge.h"

extern int Board[SIZE][SIZE];
int directions[8][2] = { {1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1} };



int liveFour1[6] = { 0,2,2,2,2,0 };

int chongFour1[5] = { 2,2,0,2,2 };
int chongFour2[6] = { 0,2,2,2,2,1 };
int chongFour3[6] = { 1,2,2,2,2,0 };
int chongFour4[5] = { 2,0,2,2,2 };
int chongFour5[5] = { 2,2,2,0,2 };

int liveThree1[5] = { 0,2,2,2,0 };
int liveThree2[6] = { 0,2,2,0,2,0 };
int liveThree3[6] = { 0,2,0,2,2,0 };

int sleepThree1[5] = { 2,0,2,0,2 };
int sleepThree2[6] = { 1,2,2,0,2,0 };
int sleepThree3[6] = { 0,2,0,2,2,1 };
int sleepThree4[6] = { 1,2,0,2,2,0 };
int sleepThree5[6] = { 0,2,2,0,2,1 };
int sleepThree6[5] = { 2,2,0,0,2 };
int sleepThree7[5] = { 2,0,0,2,2 };

int liveTwo1[5] = { 0,0,2,2,0 };
int liveTwo2[5] = { 0,2,2,0,0 };
int liveTwo3[5] = { 0,2,0,2,0 };
int liveTwo4[6] = { 0,2,0,0,2,0 };

/**********************************棋形的判断**********************************/


void readline(int line[], int m[], int color, int dir);
int shape_compare(int a1[], int a2[], int size1, int size2);

/*      1.在所下的棋子周围判断      */
int five(int m[], int color);
int live_four(int m[], int color);
int chong_four(int m[], int color);
int live_three(int m[], int color);
int sleep_three(int m[], int color);
int live_two(int m[], int color);