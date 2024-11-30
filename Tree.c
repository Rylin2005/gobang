#include "Tree.h"

/**
* 棋盘树的初始化
* @param cht 根节点
* @param xp 落子x坐标
* @param yp 落子y坐标
* @param col 落子颜色
*/
void Init_Tree(ChessTree* cht, int xp, int yp, int col)
{
	cht->alpha = -INF;
	cht->beta = INF;
	cht->color = col;
	cht->xxPos = xp;
	cht->yyPos = yp;
	cht->depth = 0;
	cht->child_num = 0;
	cht->children = NULL;
	cht->father = NULL;
}

/**
* 添加子结点
* @param[in] father 父结点
* @param[in] children 子结点数组
* @param[in] count 子结点个数
*/
void add_children(struct Node* father,struct Node* children, int count)
{
	father->children = children;
	father->child_num = count;
	for (int i = 0; i < count; i++)
	{
		children[i].depth = father->depth;
		children[i].father = father;
		children[i].color = (father->color == BLACK) ? WHITE : BLACK;
	}
}
