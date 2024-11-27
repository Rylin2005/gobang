#pragma once
#include "value.h"
#include "Tree.h"
#define DEEP 6


extern int Board[SIZE][SIZE];


int alphabeta(ChessTree* cht, struct Node* father, int deep, int alpha, int beta);
int generate(int color, struct Node* children);
