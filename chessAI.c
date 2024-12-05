#include "chessAI.h"




/**
* ʵ��alpha-beta��֦�㷨
* @param ChessTree* cht alpha-beta������Ҫ�µĵ�һ����Ϊ����
* @param Node* father ����㣨��ǰ��㣩
* @param int deep �������
* @param int alpha ��һ������alphaֵ
* @param int beta ��һ������betaֵ
* @retval int ��ǰ����value��alpha or beta��
*/
int alphabeta(ChessTree* cht, struct Node* father, int deep, int alpha, int beta)
{
	if (deep == 0)                                        //�������Ϊ��ʱ���д�֣�ȡ�����Ӳ����ط�ֵ
	{
		int e = evaluate();
		return e;
	}
	struct Node children[MAX_CHILD];
	int count_children = generate(father, children);         //��father����²�����һ���Ľ�����飨����Ҫ������
	add_children(father, children, count_children);
	if (father->color == cht->color)                                //alpha-beta��Ҫ�ݹ����
	{
		for (int i = count_children - 1; i > -1; i--)           //�����������Ҫ�ԸߵĽ��
		{
			Board[children->xxPos][children->yyPos] = father->color;
			int childvalue = alphabeta(cht, &children[i], deep - 1, father->alpha, father->beta);
			father->alpha = (father->alpha < childvalue) ? childvalue : father->alpha;
			Board[children->xxPos][children->yyPos] = 0;
			if (beta<father->alpha)
			{
				return INF;
			}
		}
	}
	else
	{
		for (int i = count_children - 1; i > -1; i--)
		{
			Board[children->xxPos][children->yyPos] = father->color;
			int childvalue = alphabeta(cht, &children[i], deep - 1, father->alpha, father->beta);
			father->beta = (father->beta > childvalue) ? childvalue : father->beta;
			Board[children->xxPos][children->yyPos] = 0;
			if (alpha > father->beta)
			{
				return -INF;
			}
		}
	}
}

/**
* ��father����²����ӽ�㣬�ӽ�������Ҫ�Դ�ֲ���С��������
* @param Node* father ��ǰ���
* @param Node* children Ҫ�������ӽ������
* @retval int �ӽ�����
*/
int generate(struct Node* father, struct Node* children)
{
	int count = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++) 
		{
			if (Board[i][j]==0 && is_around(i, j))     //������Χ������������Ĭ�ϲ��ٿ���
			{
				if (father->color == WHITE && BanMove(i, j) != 0)break;    //�����½���

				//�Ը�λ�÷ֱ��°��������д�֣�����Ҫ��Ϊ����������Ҫ��֮��
				int score = 0;
                int m[2] = { i,j };
				Board[i][j] = father->color;
				score += score_for_generate(m, Board[i][j]);
				Board[i][j] = (father->color == BLACK) ? WHITE : BLACK;
				score += score_for_generate(m, Board[i][j]);

				//��ʼ��children����
				struct Node child; 
				Init_Tree(&child, i, j, Board[i][j]);
				children[count] = child;
				children[count].score = score;
			}
		}
	}
	qsort(children, 0, count - 1);
	return count;
}

/**
* Ӧ����generate()�Ĵ�ֺ���
* @param int m[] ����λ��
* @param int color ������ɫ
* @retval int �õ�ķ���
*/
int score_for_generate(int m[], int color)
{
	if (five(m, color) != 0 || live_four(m, color) != 0)return INF;
	
	int chong4 = chong_four(m, color);
	int live3 = live_three(m, color);
	int sleep3 = sleep_three(m, color);
	int live2 = live_two(m, color);
	if (chong4 > 1 || live3 > 1)return INF;
	return chong4 * CHONGFOUR + live3 * LIVETHREE + sleep3 * SLEEPTHREE + live2 * LIVETWO;
}

/**
* �ж����Ӵ���Χ3�����Ƿ�������
* @param x ���������
* @param y ���������
* @retval 0 ��Χû������
* @retval 1 ��Χ������
*/
int is_around(int x, int y)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 1; j < 4; j++) 
		{
			int m0 = x + j * directions[i][0];
			int m1 = y + j * directions[i][1];
			if (Board[m0][m1]!=0)
			{
				return 1;
			}
		}
	}
	return 0;
}

int evaluate()
{
	//���������������
	return 0;
}

/*
	��ʵ�֣� 1.����ʽ���� ���̣�
			2.��������
			3.Zobrist����
			4.��ɱ
			5.��������
			6.�ֲ���������
			7.���ֶ�ʽ
*/