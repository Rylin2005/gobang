#include <stdio.h>
#include "value.h"

int Board[SIZE][SIZE];

void InitBoardArray();                        //��ʼ��������
void DisplayBoard();	                      //��ʾ����
int getInput(int m[], int color);       //��ȡ����λ�����벢��������

void main()
{
	int color;              //��ǰִ����ɫ
	int ending = 1;         //��ֽ�����ending=0
	int input[2];           //�������������
	int err = 1;            //�Ƿ���ڷǷ�����
	int moveCount = 0;      //�����Ѿ����еĲ���

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
			printf("%s\n","���������룺");
		}
	}


}


//����λ�ó�ʼ��Ϊ0
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
				printf("��");
				break;

			case 2:
				printf("��");
				break;

			case 8:
				printf("��");
				break;

			case 6:
				printf("��");
				break;

			case 3:
				printf("��");
				break;

			case 1:
				printf("��");
				break;

			case 5:
				printf("��");
				break;

			case 7:
				printf("��");
				break;

			case 4:
				printf("��");
				break;

			case BLACKtem:      // ������һ��
				printf("��");
				Board[i][j] = BLACK;
				break;

			case WHITEtem:      //������һ��
				printf("��");
				Board[i][j] = WHITE;
				break;

			case BLACK:      //����ͨ��
				printf("��");
				break;

			case WHITE:
				printf("��");  //����ͨ��
				break;
			}

			if (j != SIZE - 1)   //��ȫ����
			{
				if (i == 0 || i == SIZE - 1)
					printf("��");
				else
					printf("��");
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
	 *˵����m[0]��Board��������m[1]��Board������
	 *���벻���ִ�Сд������������ʽ��(����)��a3,A3,3a,a   3
	 *err=0ʱ��ʾ���뷶Χ�������⣬err=1ʱ��ʾ���뷶Χ��������
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
	//�ж������Ƿ�Ϸ�
	if (m[0]<15 && m[0]>-1 && m[1]<15 && m[1]>-1 && Board[m[0]][m[1]] == 0)
		err = 1;
	else
		err = 0;
	if(err)
		Board[m[0]][m[1]] = color;
	return err;
}

