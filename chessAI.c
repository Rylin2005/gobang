#include "chessAI.h"
keynum = 0;



/**
* 实现alpha-beta剪枝算法
* @param ChessTree* cht alpha-beta树（以要下的第一个子为根）
* @param Node* father 父结点（当前结点）
* @param int deep 迭代深度
* @param int alpha 上一级结点的alpha值
* @param int beta 上一级结点的beta值
* @retval int 当前结点的value（alpha or beta）
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
	if (deep == 0)                                        //迭代深度为零时进行打分，取消落子并返回分值
	{
		int e = evaluate(cht, father);
		//father->alpha = e; ////
		return e;
	}
	struct Node* children[MAX_CHILD];
	int count_children = generate(father, children);         //在father结点下产生下一步的结点数组（按重要性排序）
	add_children(father, children, count_children);
	if (father->color == cht->color)                                //alpha-beta主要递归代码
	{
		for (int i = 0; i < count_children ; i++)           //先深度搜索重要性高的结点
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
* 在father结点下产生子结点，子结点根据重要性打分并从小到大排序
* @param Node* father 当前结点
* @param Node* children 要产生的子结点数组
* @retval int 子结点个数
*/
int generate(struct Node* father, struct Node* children[])
{
	int count = 0;
	struct Node* child_buf[SIZE * SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++) 
		{
			if (Board[i][j]==0 && is_around(i, j) == 1)     //落子周围三格内无棋子默认不再考虑
			{
				int isbanmove = 0;
				if (father->color == BLACK)    //避免下禁手
				{
					Board[i][j] = BLACK;
					if (BanMove(i, j) != 0)
						isbanmove = 1;
					Board[i][j] = 0;
				}
				if (isbanmove == 1)break;

				//对该位置分别下白棋黑棋进行打分，其重要性为对两方的重要性之和
				int score = 0;
                int m[2] = { i,j };
				Board[i][j] = father->color;
				score += score_for_generate(m, Board[i][j]);
				Board[i][j] = (father->color == BLACK) ? WHITE : BLACK;
				score += score_for_generate(m, Board[i][j]);
				Board[i][j] = 0;

				//初始化children数组
				struct Node* child = (ChessTree*)malloc(sizeof(ChessTree)); 
				Init_Tree(child, i, j, Board[i][j], INT_MIN);
				child_buf[count] = child;
				child_buf[count] -> score = score;

				//处理指针
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
			free(child_buf[i]);   //释放无用内存
			child_buf[i] = NULL;
		}
			
	}
	return (count > MAX_CHILD) ? MAX_CHILD : count;
}

/**
* 应用于generate()的打分函数
* @param int m[] 落子位置
* @param int color 棋子颜色
* @retval int 该点的分数
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
* 判断落子处周围5*5范围内是否有棋子
* @param x 数组的列数
* @param y 数组的行数
* @retval 0 周围没有棋子
* @retval 1 周围有棋子
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
* 评估棋盘整体分数
* @param ChessTree* cht 根节点
* @param Node* np 当前节点
* @retval int 当前棋局整体评估值
*/
int evaluate(ChessTree* cht, struct Node* np)
{
	if (np->evalue != INT_MIN)             //如果np结点已经做了整体评估
		return np->evalue;                  //返回评估值
	Board[np->xxPos][np->yyPos] = 0;       //退回该步
	int past_value = evaluate(cht, np->father);       //获得上一个结点的评估值

	int m[2] = { np->xxPos,np->yyPos };
	int opcolor = (cht->color == BLACK) ? WHITE : BLACK;

	//采用负极大值评估，即对手的分值取负值
	int value_a = score_for_generate(m, cht->color) - score_for_generate(m, opcolor);   //未下子的值
	Board[np->xxPos][np->yyPos] = (np->color == BLACK) ? WHITE : BLACK;											//落子
	int value_b = score_for_generate(m, cht->color) - score_for_generate(m, opcolor);   //落子后的值
	np->evalue = past_value + value_b - value_a;
	return np->evalue;
}

/**
* 在构建好的alpha-beta树中随机取一个最优解
* @param ChessTree* cht 棋盘树
* @retval Node* 下一步应走的结点
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
	待实现： 1.启发式评估 （√）
			2.迭代加深
			3.Zobrist缓存
			4.算杀
			5.冲四延伸
			6.局部评估方法
			7.开局定式
*/
