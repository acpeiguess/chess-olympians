#ifndef AI_H
#define AI_H

#include "Pieces.h"
#include "Board.h"
#include "Rules.h"

#include <time.h>

#define DEPTH 4
#define ALPHA0 -2000000000
#define BETA0 2000000000

typedef struct Node
{
	t_player turn;
	int pointTotal;
	t_piece *board[8][8];
	
	struct Node *up, *down;

} s_Node;

typedef struct Move
{
	t_coords pieceLoc;
	t_coords pieceDest;
	int alpha
} t_move;

s_Node* createRoot(t_piece *board[8][8], t_player turn);

void addMove(s_Node *parentNode, int isMin, t_coords loc1, t_coords loc2);

void murderChild(s_Node *parentNode);

t_move findBestMove(t_piece *board[8][8], t_player turn, int maxDepth);

int maxMove(int alpha, int beta, int depthLeft, s_Node* Node);

int minMove(int alpha, int beta, int depthLeft, s_Node* Node);




#endif
