#include "Tree.h"

/**
* 棋盘树的初始化
* @param cht 根节点
* @param xp 落子x坐标
* @param yp 落子y坐标
* @param col 落子颜色
* @param 当前棋盘整体分数
*/
void Init_Tree(ChessTree* cht, int xp, int yp, int col, int evalue)
{
	cht->alpha = -INF;
	cht->beta = INF;
	cht->color = col;
	cht->xxPos = xp;
	cht->yyPos = yp;
	cht->depth = 0;
	cht->child_num = 0;
	cht->father = NULL;
	cht->evalue = evalue;
	for (int i = 0; i < MAX_CHILD; i++)
		cht->children[i] = NULL;
}

/**
* 添加子结点
* @param[in] father 父结点
* @param[in] children 子结点数组
* @param[in] count 子结点个数
*/
void add_children(struct Node* father,struct Node* children[], int count)
{
	for (int i = 0; i < MAX_CHILD; i++)
	{
		father->children[i] = children[i];
	}
	father->child_num = count;
	for (int i = 0; i < count; i++)
	{
		father->children[i]->depth = father->depth + 1;
		father->children[i]->father = father;
		father->children[i]->color = (father->color == BLACK) ? WHITE : BLACK;
		father->children[i]->evalue = INT_MIN;    //取INT_MIN代表当前为进行棋盘整体评估
	}
}

int free_tree(ChessTree* cht)
{
	if (cht != NULL)
	{
		if (cht->child_num == 0)
		{
			free(cht);
			return 1;
		}
		else
		{
			for (int i = 0; i < cht->child_num; i++)
				free_tree(cht->children[i]);
			free(cht);
			return 1;
		}
	}
	printf("error: failed to free tree...\n");
	return 0;
}
