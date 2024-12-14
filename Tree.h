#pragma once
#ifndef TREE_H
#define TREE_H


#include "value.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * �������Ľ�� 
 * @param int alpha �ý���alphaֵ�����ֵ��
 * @param int beta �ý���betaֵ����Сֵ��
 * @param int xxPos �ý�����ӵ�x����
 * @param int yyPos �ý�����ӵ�y����
 * @param int color ִ����ɫ
 * @param int depth �������
 * @param int score ���ķ���������ʽ������Ҫ��
 * @param int evalue �����������������������Ҫ��
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
	int evalue;
	struct Node* children[MAX_CHILD];
	struct Node* father;
}ChessTree;

void Init_Tree(ChessTree* cht, int xp, int yp, int col, int evalue);
void add_children(struct Node* father,struct Node* children[], int count);
int free_tree(ChessTree* cht);

#endif // !TREE_H
