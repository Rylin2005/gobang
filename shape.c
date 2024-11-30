#include "shape.h"

void readline(int line[], int m[], int color, int dir)
{
	for (int i = -4; i < 5; i++)
	{
		int m0 = m[0] + i * directions[dir][0];
		int m1 = m[1] + i * directions[dir][1];
		if (m0 < 0 || m0>14 || m1 < 0 || m1>14)
		{
			line[i + 4] = 1;
		}
		int co = Board[m0][m1];
		if (co == color)
		{
			line[i + 4] = 2;    //同色棋子
		}
		else if (co == 0)
		{
			line[i + 4] = 0;
		}
		else
		{
			line[i + 4] = 1;    //异色棋子
		}
	}
}

int shape_compare(int a1[], int a2[], int size1, int size2)
{
	for (int i = 0; i < size1 - size2 + 1; i++)
	{
		int eq = 1;
		for (int j = 0; j < size2; j++)
		{
			eq *= (a1[i + j] == a2[j]);
		}
		if (eq)return 1;
	}
	return 0;
}

/*      1.在所下的棋子周围判断      */

int five(int m[], int color)
{
	return judgeWin(m, color);
}

int live_four(int m[], int color)
{
	int live4 = 0;
	for (int i = 0; i < 4; i++)
	{
		int line[9] = { 0,0,0,0,0,0,0,0,0 };
		readline(line, m, color, i);
		live4 += shape_compare(line, liveFour1, 9, 6);
	}
	return live4;
}

int chong_four(int m[], int color)
{
	int chong4 = 0;
	for (int i = 0; i < 4; i++)
	{
		int line[9] = { 0,0,0,0,0,0,0,0,0 };
		readline(line, m, color, i);
		chong4 = chong4 + shape_compare(line, chongFour1, 9, 5)
			+ shape_compare(line, chongFour2, 9, 6)
			+ shape_compare(line, chongFour3, 9, 6)
			+ shape_compare(line, chongFour4, 9, 5)
			+ shape_compare(line, chongFour5, 9, 5);
	}
	return chong4;
}

int live_three(int m[], int color)
{
	int live3 = 0;
	for (int i = 0; i < 4; i++)
	{
		int line[9] = { 0,0,0,0,0,0,0,0,0 };
		readline(line, m, color, i);
		live3 = live3 + shape_compare(line, liveThree1, 9, 5)
			+ shape_compare(line, liveThree2, 9, 6)
			+ shape_compare(line, liveThree3, 9, 6);
	}
	return live3;
}

int sleep_three(int m[], int color)
{
	int sleep3 = 0;
	for (int i = 0; i < 4; i++)
	{
		int line[9] = { 0,0,0,0,0,0,0,0,0 };
		readline(line, m, color, i);
		sleep3 = sleep3 + shape_compare(line, sleepThree1, 9, 5)
			+ shape_compare(line, sleepThree2, 9, 6)
			+ shape_compare(line, sleepThree3, 9, 6)
			+ shape_compare(line, sleepThree4, 9, 6)
			+ shape_compare(line, sleepThree5, 9, 6)
			+ shape_compare(line, sleepThree6, 9, 5)
			+ shape_compare(line, sleepThree7, 9, 5);
	}
	return sleep3;
}

int live_two(int m[], int color)
{
	int live2 = 0;
	for (int i = 0; i < 4; i++)
	{
		int line[9] = { 0,0,0,0,0,0,0,0,0 };
		readline(line, m, color, i);
		live2 = live2 + shape_compare(line, liveTwo1, 9, 5)
			+ shape_compare(line, liveTwo2, 9, 5)
			+ shape_compare(line, liveTwo3, 9, 5)
			+ shape_compare(line, liveTwo4, 9, 6);
	}
	return live2;
}