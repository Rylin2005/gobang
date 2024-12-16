#include "chessAI.h"
keynum = 0;



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
	int m[2] = { father->xxPos,father->yyPos };
	if (five(m, (father->color == BLACK) ? WHITE : BLACK))
	{
		if (father->color == cht->color)
			return -INF;
		else
			return INF;
	}
	if (deep == 0)                                        //�������Ϊ��ʱ���д�֣�ȡ�����Ӳ����ط�ֵ
	{
		int e = evaluate(cht, father);
		//father->alpha = e; ////
		return e;
	}
	struct Node* children[MAX_CHILD];
	int count_children = generate(father, children);         //��father����²�����һ���Ľ�����飨����Ҫ������
	add_children(father, children, count_children);
	if (father->color == cht->color)                                //alpha-beta��Ҫ�ݹ����
	{
		for (int i = 0; i < count_children ; i++)           //�����������Ҫ�ԸߵĽ��
		{
			Board[children[i]->xxPos][children[i]->yyPos] = father->color;
			int childvalue = alphabeta(cht, children[i], deep - 1, father->alpha, father->beta);
			father->alpha = (father->alpha < childvalue) ? childvalue : father->alpha;
			Board[children[i]->xxPos][children[i]->yyPos] = 0;
			if (beta<father->alpha)
			{
				return INF;
			}
		}
		return father->alpha;
	}
	else
	{
		for (int i = 0; i < count_children; i++)
		{
			Board[children[i]->xxPos][children[i]->yyPos] = father->color;
			int childvalue = alphabeta(cht, children[i], deep - 1, father->alpha, father->beta);
			father->beta = (father->beta > childvalue) ? childvalue : father->beta;
			Board[children[i]->xxPos][children[i]->yyPos] = 0;
			if (alpha > father->beta)
			{
				return -INF;
			}
		}
		return father->beta;
	}
}

/**
* ��father����²����ӽ�㣬�ӽ�������Ҫ�Դ�ֲ���С��������
* @param Node* father ��ǰ���
* @param Node* children Ҫ�������ӽ������
* @retval int �ӽ�����
*/
int generate(struct Node* father, struct Node* children[])
{
	int count = 0;
	struct Node* child_buf[SIZE * SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++) 
		{
			if (Board[i][j]==0 && is_around(i, j) == 1)     //������Χ������������Ĭ�ϲ��ٿ���
			{
				int isbanmove = 0;
				if (father->color == BLACK)    //�����½���
				{
					Board[i][j] = BLACK;
					if (BanMove(i, j) != 0)
						isbanmove = 1;
					Board[i][j] = 0;
				}
				if (isbanmove == 1)break;

				//�Ը�λ�÷ֱ��°��������д�֣�����Ҫ��Ϊ����������Ҫ��֮��
				int score = 0;
                int m[2] = { i,j };
				Board[i][j] = father->color;
				score += score_for_generate(m, Board[i][j]);
				Board[i][j] = (father->color == BLACK) ? WHITE : BLACK;
				score += score_for_generate(m, Board[i][j]);
				Board[i][j] = 0;

				//��ʼ��children����
				struct Node* child = (ChessTree*)malloc(sizeof(ChessTree)); 
				Init_Tree(child, i, j, Board[i][j], INT_MIN);
				child_buf[count] = child;
				child_buf[count] -> score = score;

				//����ָ��
				child = NULL;
				count++;
			}
		}
	}
	qsort(child_buf, 0, count - 1);
	for (int i = 0; i < count; i++)
	{
		if (i < MAX_CHILD)
		{
			children[i] = child_buf[i];
		}
		else
		{
			free(child_buf[i]);   //�ͷ������ڴ�
			child_buf[i] = NULL;
		}
			
	}
	return (count > MAX_CHILD) ? MAX_CHILD : count;
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
	if (chong4 > 1 || live3 > 1)return LIVEFOUR;
	return chong4 * CHONGFOUR + live3 * LIVETHREE + sleep3 * SLEEPTHREE + live2 * LIVETWO;
}

/**
* �ж����Ӵ���Χ5*5��Χ���Ƿ�������
* @param x ���������
* @param y ���������
* @retval 0 ��Χû������
* @retval 1 ��Χ������
*/
int is_around(int x, int y)
{
	for (int i = 1; i < 3; i++)
	{
		for (int j = 0; j < 8; j++) 
		{
			int m0 = x + i * directions[j][0];
			int m1 = y + i * directions[j][1];
			if (m0 > -1 && m0<SIZE && m1>-1 && m1 < SIZE)
			{
				if (Board[m0][m1] != 0)
					return 1;
			}
		}
	}
	return 0;
}

/**
* ���������������
* @param ChessTree* cht ���ڵ�
* @param Node* np ��ǰ�ڵ�
* @retval int ��ǰ�����������ֵ
*/
int evaluate(ChessTree* cht, struct Node* np)
{
	if (np->evalue != INT_MIN)             //���np����Ѿ�������������
		return np->evalue;                  //��������ֵ
	Board[np->xxPos][np->yyPos] = 0;       //�˻ظò�
	int past_value = evaluate(cht, np->father);       //�����һ����������ֵ

	int m[2] = { np->xxPos,np->yyPos };
	int opcolor = (cht->color == BLACK) ? WHITE : BLACK;

	//���ø�����ֵ�����������ֵķ�ֵȡ��ֵ
	int value_a = score_for_generate(m, cht->color) - score_for_generate(m, opcolor);   //δ���ӵ�ֵ
	Board[np->xxPos][np->yyPos] = (np->color == BLACK) ? WHITE : BLACK;											//����
	int value_b = score_for_generate(m, cht->color) - score_for_generate(m, opcolor);   //���Ӻ��ֵ
	np->evalue = past_value + value_b - value_a;
	return np->evalue;
}

/**
* �ڹ����õ�alpha-beta�������ȡһ�����Ž�
* @param ChessTree* cht ������
* @retval Node* ��һ��Ӧ�ߵĽ��
*/
struct Node* findMax(ChessTree* cht)
{
	int num = 0;
	struct Node* maxNode[MAX_CHILD];
	for (int i = 0; i < cht->child_num; i++)
	{
		if (cht->alpha == cht->children[i]->beta && num < 10)
		{
			maxNode[num] = cht->children[i];
			num++;
		}
	}

	srand((unsigned)time(NULL));
	int n = rand() % num;
	return maxNode[n];
}


void InitZobrist()
{
	srand((unsigned)time(NULL));
	key_of_board = produce_rand32bit();
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			BlackZobrist[i][j] = produce_rand32bit();
			WhiteZobrist[i][j] = produce_rand32bit();
		}
	}
}

unsigned int produce_rand32bit()
{
	unsigned int rand32bit = 0;
	for (int i = 0; i < 4; i++)
	{
		rand32bit = rand32bit << (8);
		int a = rand() % 256;
		rand32bit += a;
	}
	return rand32bit;
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
