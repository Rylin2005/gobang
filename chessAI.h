#pragma once

#include "value.h"
#include "Tree.h"
#include "shape.h"
#include "judge.h"
#include "quick_sort.h"
#define DEEP 6    //搜索深度默认为6

extern int directions[8][2];

extern int Board[SIZE][SIZE];


int alphabeta(ChessTree* cht, struct Node* father, int deep, int alpha, int beta);
int generate(struct Node* father, struct Node* children);
int evaluate();

int score_for_generate(int m[], int color);
int is_around(int x, int y); 

