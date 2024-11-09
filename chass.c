#include <stdio.h>
#include "value.h"

int Board[SIZE][SIZE];

void InitBoardArray();                        //初始化空棋盘
void DisplayBoard();	                      //显示棋盘
int getInput(int m[], int color);       //获取棋子位置输入并更新棋盘

void main()
{
	int color;              //当前执棋颜色
	int ending = 1;         //棋局结束：ending=0
	int input[2];           //输入的棋盘坐标
	int err = 1;            //是否存在非法输入
	int moveCount = 0;      //棋盘已经进行的步数

	InitBoardArray();
	DisplayBoard();

	while (ending)
	{
		if (moveCount % 2 == 0)
			err = getInput(input, BLACKtem, err);
		else
			err = getInput(input, WHITEtem, err);
		if (err)
		{
			moveCount++;
			DisplayBoard();
		}
		else
		{
			printf("%s\n","请重新输入：");
		}
	}


}


//将空位置初始化为0
void InitBoardArray()
{
	int j, i;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			Board[i][j] = 0;
		}
	}
}

void DisplayBoard() {
	int i, j, k;
	char line = SIZE;
	char ary;
	system("cls");
	for (i = 0; i < SIZE; i++)
	{
		printf("%2d", line);
		line -= 1;
		for (j = 0; j < SIZE; j++)
		{
			if (Board[i][j] == 0)
				k = ((i > 0) + (i == (SIZE - 1))) * 3 + ((j > 0) + (j == (SIZE - 1)));
			else
				k = Board[i][j];
			switch (k)
			{
			case 0:
				printf("┏");
				break;

			case 2:
				printf("┓");
				break;

			case 8:
				printf("┛");
				break;

			case 6:
				printf("┗");
				break;

			case 3:
				printf("┠");
				break;

			case 1:
				printf("┯");
				break;

			case 5:
				printf("┨");
				break;

			case 7:
				printf("┷");
				break;

			case 4:
				printf("┼");
				break;

			case BLACKtem:      // 黑子上一步
				printf("▲");
				Board[i][j] = BLACK;
				break;

			case WHITEtem:      //白子上一步
				printf("△");
				Board[i][j] = WHITE;
				break;

			case BLACK:      //黑子通常
				printf("●");
				break;

			case WHITE:
				printf("○");  //白子通常
				break;
			}

			if (j != SIZE - 1)   //补全横线
			{
				if (i == 0 || i == SIZE - 1)
					printf("━");
				else
					printf("─");
			}

			if (j == SIZE - 1)
			{
				printf("\n");
			}

		}
	}

	printf("  ");
	for (ary = 'A'; ary < 'A' + SIZE; ary++)
		printf("%c ", ary);

	printf("\n");
}

int getInput(int m[], int color)
{
	/*
	 *说明：m[0]存Board的行数，m[1]存Board的列数
	 *输入不区分大小写，允许的输入格式有(例如)：a3,A3,3a,a   3
	 *err=0时表示输入范围在棋盘外，err=1时表示输入范围在棋盘内
	 */

	int c, d, err;
	c = getchar();
	while (c != EOF && c != '\n')
	{
		if (c >= '0' && c <= '9')
		{
			if ((d = getchar()) >= '0' && d <= '9')
			{
				m[0] = SIZE - (d - '0') - 10 * (c - '0');
				c = getchar();
			}
			else
			{
				m[0] = SIZE - (c - '0');
				c = d;
			}
		}
		if (c >= 'a' && c <= 'z')
		{
			m[1] = c - 'a';
			c = getchar();
		}
		else if (c >= 'A' && c <= 'Z') {
			m[1] = c - 'A';
			c = getchar();
		}
		else if (c == EOF || c == '\n');
		else
			c = getchar();
	}
	//判断输入是否合法
	if (m[0]<15 && m[0]>-1 && m[1]<15 && m[1]>-1 && Board[m[0]][m[1]] == 0)
		err = 1;
	else
		err = 0;
	if(err)
		Board[m[0]][m[1]] = color;
	return err;
}

