#pragma once

#include <stdio.h>
#include <string.h>
#include "value.h"

//棋局裁判的实现
extern int Board[SIZE][SIZE];

int judgeWin(int m[], int color);  //判断是否胜利
int directionCount(int m[], int color, int dir); //对某方向计数

int BanMove(int x_row, int y_column);
int ThreeBan(int x_row, int y_column);
int FourBan(int x_row, int y_column);
int LongBan(int x_row, int y_column);