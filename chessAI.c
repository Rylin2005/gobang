#include "chessAI.h"



int alphabeta(ChessTree* cht, struct Node* father, int deep, int alpha, int beta)
{
	Board[father->xxPos][father->yyPos] = father->color;
	if (deep == 0)
	{
		int e = evaluate();
		Board[father->xxPos][father->yyPos] = 0;
		return e;
	}
	struct Node children[MAX_CHILD];
	int count_children = generate(father->color, children);
	add_children(father, children, count_children);
	if (father->color == cht->color)
	{
		for (int i = 0; i < count_children; i++)
		{
			int childvalue = alphabeta(cht, &children[i], deep - 1, father->alpha, father->beta);
			father->alpha = (father->alpha < childvalue) ? childvalue : father->alpha;
			if (beta<father->alpha)
			{
				Board[father->xxPos][father->yyPos] = 0;
				return INF;
			}
		}
	}
	else
	{
		for (int i = 0; i < count_children; i++)
		{
			int childvalue = alphabeta(cht, &children[i], deep - 1, father->alpha, father->beta);
			father->beta = (father->beta > childvalue) ? childvalue : father->beta;
			if (alpha > father->beta)
			{
				Board[father->xxPos][father->yyPos] = 0;
				return -INF;
			}
		}
	}
}



int generate(int father_color, struct Node* children)
{
	//return how many children generated
}

int evaluate()
{
	//评估棋盘分数
	return 0;
}

/*
	待实现： 1.启发式评估
			2.迭代加深
			3.Zobrist缓存
			4.算杀
			5.冲四延伸
			6.局部评估方法
			7.开局定式
*/
