#include "chessAI.h"
#include "shape.h"
#include "judge.h"
#include "quick_sort.h"



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
	if (deep == 0)                                        //迭代深度为零时进行打分，取消落子并返回分值
	{
		int e = evaluate();
		return e;
	}
	struct Node children[MAX_CHILD];
	int count_children = generate(father, children);         //在father结点下产生下一步的结点数组（按重要性排序）
	add_children(father, children, count_children);
	if (father->color == cht->color)                                //alpha-beta主要递归代码
	{
		for (int i = count_children - 1; i > -1; i--)           //先深度搜索重要性高的结点
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
* 在father结点下产生子结点，子结点根据重要性打分并从小到大排序
* @param Node* father 当前结点
* @param Node* children 要产生的子结点数组
* @retval int 子结点个数
*/
int generate(struct Node* father, struct Node* children)
{
	int count = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++) 
		{
			if (Board[i][j]==0 && is_around(i, j))     //落子周围三格内无棋子默认不再考虑
			{
				if (father->color == WHITE && BanMove(i, j) != 0)break;    //避免下禁手

				//对该位置分别下白棋黑棋进行打分，其重要性为对两方的重要性之和
				int score = 0;
                int m[2] = { i,j };
				Board[i][j] = father->color;
				score += score_for_generate(m, Board[i][j]);
				Board[i][j] = (father->color == BLACK) ? WHITE : BLACK;
				score += score_for_generate(m, Board[i][j]);

				//初始化children数组
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
	if (chong4 > 1 || live3 > 1)return INF;
	return chong4 * CHONGFOUR + live3 * LIVETHREE + sleep3 * SLEEPTHREE + live2 * LIVETWO;
}

/**
* 判断落子处周围3格内是否有棋子
* @param x 数组的列数
* @param y 数组的行数
* @retval 0 周围没有棋子
* @retval 1 周围有棋子
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
	//评估棋盘整体分数
	return 0;
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
