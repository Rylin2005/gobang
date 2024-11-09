#pragma once

#include "value.h"
//棋局裁判的实现
extern int Board[SIZE][SIZE];

int judgeWin(int m[], int color);  //判断是否胜利
int directionCount(int m[], int color, int dir); //对某方向计数

int judgeThree(int m[], int color);//判断三三禁手
int judgeFour(int m[], int color); //判断四四禁手
int judgeLong(int m[], int color); //判断长连禁手