#pragma once
#include "value.h"

/**
 * 棋盘树的结点 
 * @param int alpha 该结点的alpha值（最大值）
 * @param int beta 该结点的beta值（最小值）
 * @param int xxPos 该结点落子的x坐标
 * @param int yyPos 该结点落子的y坐标
 * @param int color 该结点的落子颜色
 * @param int depth 树的深度
 * @param Node* children 该结点的子结点数组指针
 * @param Node* father 该结点的父节点指针
 * @param int child_num 子结点的个数
 */
typedef struct Node
{
	int alpha;
	int beta;
	int xxPos;
	int yyPos;
	int color;
	int child_num;
	int depth;
	struct Node* children;
	struct Node* father
}ChessTree;

void Init_Tree(ChessTree* cht, int xp, int yp, int col);
void add_children(struct Node* father,struct Node* children, int count);
