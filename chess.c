#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "value.h"
#include "judge.h"
#include "chessAI.h"
#include "Tree.h"


//---------

int Board[SIZE][SIZE];
int directions[8][2] = { {1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1} };
int evalue_buf[SIZE * SIZE];
int bufp = 0;

//---------

int liveFour1[6] = { 0,2,2,2,2,0 };

int chongFour1[5] = { 2,2,0,2,2 };
int chongFour2[6] = { 0,2,2,2,2,1 };
int chongFour3[6] = { 1,2,2,2,2,0 };
int chongFour4[5] = { 2,0,2,2,2 };
int chongFour5[5] = { 2,2,2,0,2 };

int liveThree1[5] = { 0,2,2,2,0 };
int liveThree2[6] = { 0,2,2,0,2,0 };
int liveThree3[6] = { 0,2,0,2,2,0 };

int sleepThree1[5] = { 2,0,2,0,2 };
int sleepThree2[6] = { 1,2,2,0,2,0 };
int sleepThree3[6] = { 0,2,0,2,2,1 };
int sleepThree4[6] = { 1,2,0,2,2,0 };
int sleepThree5[6] = { 0,2,2,0,2,1 };
int sleepThree6[5] = { 2,2,0,0,2 };
int sleepThree7[5] = { 2,0,0,2,2 };

int liveTwo1[6] = { 0,0,2,2,0,0 };
int liveTwo2[6] = { 0,0,2,2,0,1 };
int liveTwo5[6] = { 1,0,2,2,0,0 };
int liveTwo3[5] = { 0,2,0,2,0 };
int liveTwo4[6] = { 0,2,0,0,2,0 };
//----------



//----------

void InitBoardArray();                        //��ʼ��������
void DisplayBoard();	                      //��ʾ����
int getInput(int m[], int color);			  //��ȡ����λ�����벢��������
void p_vs_p();								  //���˶�սģʽ����
void p_vs_c(int role);						  //�˻���սģʽ����
void chess_ai(int color, int m[]);			  //gobang ai
void push_evalue(int e);                      //����ǰ�������ӵ�buffer��
int pop_evalue();							  //��buffer��pop����ǰ�����ֵ
void debug_for_chess_ai();                    //for debug
void simulate_for_ai(int steps[][2], ChessTree* cht, int deep, struct Node* np);//չʾaiģ���������·��(for debug)


void main()
{
	int mod;				//��սģʽ
	int role;				//����ִ����ɫ
	//���� begin

	//end

	printf("������(Gobang)��ս����Ϸ����\n");
	printf("1. �ڷ�(��)���£��׷�(��)���� \n");
	printf("2. �ڷ����������֡����Ľ��֡��������ֹ��� \n");
	printf("3. ���������ȼ����ڽ��ֹ��� \n");
	printf("4. �������ֲ������ٻ�������� \n");
	printf("5. �����ֶ�սģʽ������(p)���˻�(m)��\n");
	printf("��սģʽѡ��p/m����");
	mod = getchar();
	getchar();
	if (mod == 'm')
	{
		printf("ѡ����Է� ִ��(b)/ִ��(w):");
		role = getchar();
		getchar();
	}
	printf("��ʼ����ɣ����������ʼ... \n");
	getchar();
	InitBoardArray();
	DisplayBoard();
	printf("���벻���ִ�Сд������������ʽ��(����)��a3,A3,3a,a   3 \n");

	if (mod == 'p')
		p_vs_p();
	else
		p_vs_c(role);

}

/**
 * @brief ����λ�ó�ʼ��Ϊ0
 * @param[in] ��
 * @retval ��
 */
void InitBoardArray()
{
	int j, i;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			Board[i][j] = 0;
		}
	}
}

/**
 * @brief �������
 * @param[in] ��
 * @retval ��
 */
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

/**
 * @brief ��ȡ��������
 * @param[in] m (x,y)����
 * @param[in] color ��ɫ������BLACK or WHITE��
 * @retval 0 �Ƿ�����
 * @retval 1 �Ϸ�����
 */
int getInput(int m[], int color)
{
	/**
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
	return err;
}

void p_vs_p()
{
	int color;              //��ǰִ����ɫ
	int ending = 1;         //��ֽ�����ending=0
	int input[2];           //�������������
	int err = 1;            //�Ƿ���ڷǷ�����
	int moveCount = 0;      //�����Ѿ����еĲ���
	int result = 0;         //���

	while (ending)
	{

		if (moveCount % 2 == 0)
		{
			printf("�ڷ�ִ��,�����ӣ�");
			color = BLACK;
			err = getInput(input, BLACKtem) && !(input[0] == 7 && input[1] == 7 && moveCount == 0);
			if(err)
				Board[input[0]][input[1]] = BLACKtem;
		}
		else
		{
			printf("�׷�ִ��,�����ӣ�");
			color = WHITE;
			err = getInput(input, WHITEtem);
			if (err)
				Board[input[0]][input[1]] = WHITEtem;
		}

		if (err)
		{
			moveCount++;
			DisplayBoard();
		}
		else
		{
			printf("%s\n", "����λ�ò�����Ҫ�����������룺");
			continue;
		}

		result = judgeWin(input, color);
		if (result != 0)ending = 0;
	}

	if (result == 1) {
		printf("����ʤ����");
	}
	else if (result == 2) {
		printf("����ʤ����");
	}
	else if (result == 3) {
		printf("������֣�����ʤ����");
	}
}

void p_vs_c(int role)
{
	int color;              //��ǰִ����ɫ
	int ending = 1;         //��ֽ�����ending=0
	int input[2] = {7, 7};  //�������������
	int err = 1;            //�Ƿ���ڷǷ�����
	int moveCount = 0;      //�����Ѿ����еĲ���
	int result = 0;         //���
	int steps[DEEP][2];

	push_evalue(0);
	while (ending)
	{
		if (moveCount % 2 == 0)
		{
			color = BLACK;
			if (role == 'b')
			{
				debug_for_chess_ai();
				printf("(���)-�������ڣ�%c%d\n", input[1]+ 'A', SIZE - 1 - input[0] + 1);
				printf("(����)-�ڷ�ִ��,˼����...\n");
				if (moveCount == 0)
				{
					Board[7][7] = BLACKtem;
				}
				else
				{
					chess_ai(BLACK, input);
				}
			}
			else
			{
				if (moveCount == 0)
				{
					Board[input[0]][input[1]] = BLACK;
				}
				else
				{
					debug_for_chess_ai();
					printf("(����)-�������ڣ�%c%d\n", input[1] + 'A', SIZE - 1 - input[0] + 1);
					printf("(���)-�ڷ�ִ��,�����ӣ�");
					err = getInput(input, BLACKtem) && !(input[0] == 7 && input[1] == 7 && moveCount == 0);
					if (err)
					{
						int value_a = score_for_generate(input, WHITE) - score_for_generate(input, BLACK);   //δ���ӵ�ֵ
						Board[input[0]][input[1]] = BLACK;											//����
						int value_b = score_for_generate(input, WHITE) - score_for_generate(input, BLACK);   //���Ӻ��ֵ
						int v = evalue_buf[bufp - 1];
						push_evalue(v + value_b - value_a);
						Board[input[0]][input[1]] = BLACKtem;
					}
				}
			}
		}
		else
		{
			color = WHITE;
			if (role == 'w')
			{
				debug_for_chess_ai();
				printf("(���)-�������ڣ�%c%d\n", input[1] + 'A', SIZE - 1 - input[0] + 1);
				printf("(����)-�׷�ִ��,˼����...\n");
				chess_ai(WHITE, input);
			}
			else
			{
				debug_for_chess_ai();
				printf("(����)-�������ڣ�%c%d\n", input[1] + 'A', SIZE - 1 - input[0] + 1);
				printf("(���)-�׷�ִ��,�����ӣ�");
				color = WHITE;
				err = getInput(input, WHITEtem);
				if (err)
				{
					int value_a = score_for_generate(input, BLACK) - score_for_generate(input, WHITE);   //δ���ӵ�ֵ
					Board[input[0]][input[1]] = WHITE;											         //����
					int value_b = score_for_generate(input, BLACK) - score_for_generate(input, WHITE);   //���Ӻ��ֵ
					int v = evalue_buf[bufp - 1];
					push_evalue(v + value_b - value_a);
					Board[input[0]][input[1]] = WHITEtem;
				}
			}
		}

		if (err)
		{
			moveCount++;
			DisplayBoard();
		}
		else
		{
			printf("%s\n", "����λ�ò�����Ҫ�����������룺");
			continue;
		}

		result = judgeWin(input, color);
		if (result != 0)ending = 0;
	}

	if (result == 1) {
		printf("����ʤ����");
	}
	else if (result == 2) {
		printf("����ʤ����");
	}
	else if (result == 3) {
		printf("������֣�����ʤ����");
	}
}

void chess_ai(int color, int m[])
{
	ChessTree* cht = (ChessTree*)malloc(sizeof(ChessTree));
	Init_Tree(cht, -1, -1, color, evalue_buf[bufp - 1]);
	alphabeta(cht, cht, DEEP, INF, INF);
	struct Node* max = findMax(cht);
	Board[max->xxPos][max->yyPos] = (color == BLACK) ? BLACKtem : WHITEtem;
	push_evalue(max->evalue);
	m[0] = max->xxPos;
	m[1] = max->yyPos;
	max = NULL;
	free_tree(cht);
}

void push_evalue(int e)
{
	if (bufp < SIZE*SIZE + 1)
	{
		evalue_buf[bufp] = e;
		bufp++;
	}
	else
		printf("error: evalue_buf is full...\n");
}

int pop_evalue()
{
	if (bufp > 0)
		return evalue_buf[--bufp];
	else
		printf("error: evalue_buf is empty...\n");
}

void debug_for_chess_ai()
{
	printf("��ǰ���̷�ֵ��evalue_buf[%d]=%d\n",bufp - 1 , evalue_buf[bufp - 1]);
}

void simulate_for_ai(int steps[][2], ChessTree* cht, int deep, struct Node* np)
{
	for (int i = 0; i < np->child_num; i++)
	{
		
	}
}


