#include "Tree.h"

/**
* �������ĳ�ʼ��
* @param cht ���ڵ�
* @param xp ����x����
* @param yp ����y����
* @param col ������ɫ
* @param ��ǰ�����������
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
* ����ӽ��
* @param[in] father �����
* @param[in] children �ӽ������
* @param[in] count �ӽ�����
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
		father->children[i]->evalue = INT_MIN;    //ȡINT_MIN����ǰΪ����������������
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
