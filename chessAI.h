#pragma once
#ifndef CHESS_AI_H
#define CHESS_AI_H


#include <stdlib.h>
#include "value.h"
#include "Tree.h"
#include "shape.h"
#include "judge.h"
#include "quick_sort.h"
#define DEEP 6    //搜索深度默认为6

extern int directions[8][2];
extern int Board[SIZE][SIZE];


unsigned int BlackZobrist[SIZE][SIZE];                //黑棋的zobrist哈希表
unsigned int WhiteZobrist[SIZE][SIZE];				  //白棋的zobrist哈希表
unsigned int key_of_board;							  //棋盘的键值
long long key_value[SIZE * SIZE][2];                  //键值-分值对
int keynum;                                           //键值个数



int alphabeta(ChessTree* cht, struct Node* father, int deep, int alpha, int beta);
int generate(struct Node* father, struct Node* children[]);
int evaluate(ChessTree* cht, struct Node* np);
struct Node* findMax(ChessTree* cht);

int score_for_generate(int m[], int color);
int is_around(int x, int y); 

void InitZobrist();                           //初始化哈希值
unsigned int produce_rand32bit();	          //产生32位随机数(默认uint为32位)

#endif // !CHESS_AI_H