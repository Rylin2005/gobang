#pragma once
#ifndef CHESS_AI_H
#define CHESS_AI_H


#include <stdlib.h>
#include "value.h"
#include "Tree.h"
#include "shape.h"
#include "judge.h"
#include "quick_sort.h"
#define DEEP 6    //�������Ĭ��Ϊ6

extern int directions[8][2];
extern int Board[SIZE][SIZE];


unsigned int BlackZobrist[SIZE][SIZE];                //�����zobrist��ϣ��
unsigned int WhiteZobrist[SIZE][SIZE];				  //�����zobrist��ϣ��
unsigned int key_of_board;							  //���̵ļ�ֵ
long long key_value[SIZE * SIZE][2];                  //��ֵ-��ֵ��
int keynum;                                           //��ֵ����



int alphabeta(ChessTree* cht, struct Node* father, int deep, int alpha, int beta);
int generate(struct Node* father, struct Node* children[]);
int evaluate(ChessTree* cht, struct Node* np);
struct Node* findMax(ChessTree* cht);

int score_for_generate(int m[], int color);
int is_around(int x, int y); 

void InitZobrist();                           //��ʼ����ϣֵ
unsigned int produce_rand32bit();	          //����32λ�����(Ĭ��uintΪ32λ)

#endif // !CHESS_AI_H