#include "shape.h"


void readline(int line[], int m[], int color, int dir, int num)
{
	for (int i = -num; i < num + 1; i++)
	{
		int m0 = m[0] + i * directions[dir][0];
		int m1 = m[1] + i * directions[dir][1];
		if (m0 < 0 || m0>14 || m1 < 0 || m1>14)
		{
			line[i + num] = 1;
			break;
		}
		int co = Board[m0][m1];
		if (co == color)
		{
			line[i + num] = 2;    //同色棋子
		}
		else if (co == 0)
		{
			line[i + num] = 0;
		}
		else
		{
			line[i + num] = 1;    //异色棋子
		}
	}
}




int shape_compare(int a1[], int a2[], int size1, int size2)
{
	for (int i = 0; i < size1 - size2 + 1; i++)
	{
		int j;
		for (j = 0; j < size2; j++)
		{
			if (a1[i+j]!=a2[j])
			{
				break;
			}
		}
		if (j == size2)return 1;
	}
	return 0;
}

/*      1.在所下的棋子周围判断      */

int five(int m[], int color)
{
	int nums[4];
	for (int i = 0; i < 4; i++)
	{
		nums[i] = directionCount(m, color, i) + directionCount(m, color, i + 4);
	}
	int fiveInLine = (nums[0] > 3) || (nums[1] > 3) || (nums[2] > 3) || (nums[3] > 3);
	if (fiveInLine == 0) {
		return 0;
	}
	return 1;
}

int live_four(int m[], int color)
{
	int live4 = 0;
	for (int i = 0; i < 4; i++)
	{
		int line[9] = { 0,0,0,0,0,0,0,0,0 };
		readline(line, m, color, i, 4);
		live4 += shape_compare(line, liveFour1, 9, 6);
	}
	return live4;
}

int chong_four(int m[], int color)
{
	int chong4 = 0;
	for (int i = 0; i < 4; i++)
	{
		int line[11] = { 0,0,0,0,0,0,0,0,0 };
		readline(line, m, color, i, 5);
		chong4 = chong4 + shape_compare(line, chongFour1, 11, 5)
			+ shape_compare(line, chongFour2, 11, 6)
			+ shape_compare(line, chongFour3, 11, 6)
			+ shape_compare(line, chongFour4, 11, 5)
			+ shape_compare(line, chongFour5, 11, 5);
	}
	return chong4;
}

int live_three(int m[], int color)
{
	int live3 = 0;
	for (int i = 0; i < 4; i++)
	{
		int line[9] = { 0,0,0,0,0,0,0,0,0 };
		readline(line, m, color, i, 4);
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
		readline(line, m, color, i, 4);
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
		readline(line, m, color, i, 4);
		live2 = live2 + shape_compare(line, liveTwo1, 9, 6)
			+ shape_compare(line, liveTwo2, 9, 6)
			+ shape_compare(line, liveTwo5, 9, 6)
			+ shape_compare(line, liveTwo3, 9, 5)
			+ shape_compare(line, liveTwo4, 9, 6);
	}
	return live2;
}