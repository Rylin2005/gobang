#pragma once
#include "value.h"

/**
 * �������Ľ�� 
 * @param int alpha �ý���alphaֵ�����ֵ��
 * @param int beta �ý���betaֵ����Сֵ��
 * @param int xxPos �ý�����ӵ�x����
 * @param int yyPos �ý�����ӵ�y����
 * @param int color ִ����ɫ
 * @param int depth �������
 * @param int score ���ķ���������ʽ������Ҫ��
 * @param Node* children �ý����ӽ��*����ָ��*
 * @param Node* father �ý��ĸ��ڵ�ָ��
 * @param int child_num �ӽ��ĸ���
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
	int score;
	struct Node* children;
	struct Node* father;
}ChessTree;

void Init_Tree(ChessTree* cht, int xp, int yp, int col);
void add_children(struct Node* father,struct Node* children, int count);
