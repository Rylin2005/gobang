#pragma once

#include <stdio.h>
#include <string.h>
#include "value.h"

//��ֲ��е�ʵ��
extern int Board[SIZE][SIZE];

int judgeWin(int m[], int color);  //�ж��Ƿ�ʤ��
int directionCount(int m[], int color, int dir); //��ĳ�������

int BanMove(int x_row, int y_column);
int ThreeBan(int x_row, int y_column);
int FourBan(int x_row, int y_column);
int LongBan(int x_row, int y_column);