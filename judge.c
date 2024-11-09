#include "judge.h"
#include "value.h"



int fiveInLine;   //五连及以上
int doubleThree;  //三三禁手
int doubleFour;   //四四禁手
int longline;     //长联禁手

int directions[8][2] = { {1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1} };

int judgeWin(int m[], int color)
{
	int nums[4];
	int i;
	for (i = 0; i < 4; i++) 
	{
		nums[i] = directionCount(m, color, i) + directionCount(m, color, i + 4);
	}
	int fiveInLine = (nums[0] > 4) || (nums[1] > 4) || (nums[2] > 4) || (nums[3] > 4);
	int longline = (nums[0] > 5) || (nums[1] > 5) || (nums[2] > 5) || (nums[3] > 5) || (color == BLACK);
}

int judgeThree(int m[], int color)
{
	return 0;
}

int judgeFour(int m[], int color)
{
	return 0;
}

int judgeLong(int m[], int color)
{
	return 0;
}

int directionCount(int m[], int color, int dir)
{
	int num = 0;
	int x = m[0];
	int y = m[1];

	while (Board[x][y] == color && x<15 && x>-1 && y<15 && y>-1)
	{
		num++;
		x += directions[dir][0];
		y += directions[dir][1];
	}
	return num - 1;
}
