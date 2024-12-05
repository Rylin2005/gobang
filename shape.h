#pragma once
#include "value.h"
#include "judge.h"

extern int Board[SIZE][SIZE];

extern int directions[8][2];


extern int liveFour1[6];

extern int chongFour1[5];
extern int chongFour2[6];
extern int chongFour3[6];
extern int chongFour4[5];
extern int chongFour5[5];

extern int liveThree1[5];
extern int liveThree2[6];
extern int liveThree3[6];

extern int sleepThree1[5];
extern int sleepThree2[6];
extern int sleepThree3[6];
extern int sleepThree4[6];
extern int sleepThree5[6];
extern int sleepThree6[5];
extern int sleepThree7[5];

extern int liveTwo1[5];
extern int liveTwo2[5];
extern int liveTwo3[5];
extern int liveTwo4[6];

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