#pragma once

#include "value.h"
//��ֲ��е�ʵ��
extern int Board[SIZE][SIZE];

int judgeWin(int m[], int color);  //�ж��Ƿ�ʤ��
int directionCount(int m[], int color, int dir); //��ĳ�������

int judgeThree(int m[], int color);//�ж���������
int judgeFour(int m[], int color); //�ж����Ľ���
int judgeLong(int m[], int color); //�жϳ�������