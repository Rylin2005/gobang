#include "Tree.h"

/**
* �������ĳ�ʼ��
* @param cht ���ڵ�
* @param xp ����x����
* @param yp ����y����
* @param col ������ɫ
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
* ����ӽ��
* @param[in] father �����
* @param[in] children �ӽ������
* @param[in] count �ӽ�����
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
