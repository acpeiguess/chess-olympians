#include "../inc/AI.h"

s_Node* createRoot(t_piece *board[8][8], t_player turn)
{
	s_Node *root = malloc(sizeof(s_Node));
	
	root->turn = turn;
	root->pointTotal = 0;
	copyBoard(board, root->board);
	
	root->up = NULL;
	root->down = NULL;

	return root;
}

void addMove(s_Node *parentNode, int isMin, t_coords loc1, t_coords loc2)
{
	int currentMoveValue;
	s_Node *newNode = malloc(sizeof(s_Node));
	

	/*Initialize the new node*/

	if(parentNode->turn == WHITE)
		newNode->turn = BLACK;
	else
		newNode->turn = WHITE;

	copyBoard(parentNode->board, newNode->board);
	
	newNode->pointTotal = parentNode->pointTotal;
	currentMoveValue = movePiece(newNode->board, loc1, loc2);

	if(isMin == 1)
		currentMoveValue = -1*currentMoveValue;

	newNode->pointTotal += currentMoveValue;

	newNode->up = parentNode;
	newNode->up->down = newNode;
	newNode->down = NULL;


}

void murderChild(s_Node *parentNode)
{
	free(parentNode->down); /*free their child from this cruel life*/
}

t_move findBestMove(t_piece *board[8][8], t_player turn, int maxDepth)
{
	/* calculation preparation */

	s_Node *root = createRoot(board, turn);	
	t_coords current1, current2; /*move being evaluated currently*/
	t_move bestMove;
	int alpha = ALPHA0;
	int beta = BETA0;	
	int value;

	srand(time(NULL));

	int i,j,x,y;
	int legal[8][8];

	for (i = 0; i < 8; i++) 
	{
		for (j = 0; j < 8; j++) {
			if (root->board[j][i]) {
				if (root->board[j][i]->team == root->turn) 
				{
					current1.locX = i;
					current1.locY = j;
					genLegal(current1, root->board, legal);
				
					for (y = 0; y < 8; y++) {
						for (x = 0; x < 8; x++) {
							if (legal[y][x]) 
							{ 
								 /*does not pass coordinates of the current location*/
									current2.locY = y;
									current2.locX = x;

									
									addMove(root, 0, current1, current2);
									value = minMove(alpha, beta, maxDepth-1, root->down);
									murderChild(root);
									
									if(value > alpha)
									{
										alpha = value;
										bestMove.pieceLoc.locY = current1.locY;
										bestMove.pieceLoc.locX = current1.locX;
										bestMove.pieceDest.locY = current2.locY;
										bestMove.pieceDest.locX = current2.locX;
										bestMove.alpha = alpha;
									}
									else if(value == alpha)
									{
										int chance = (rand()%100);
										if(chance < 20)
										{
											alpha = value;
											bestMove.pieceLoc.locY = current1.locY;
											bestMove.pieceLoc.locX = current1.locX;
											bestMove.pieceDest.locY = current2.locY;
											bestMove.pieceDest.locX = current2.locX;
											bestMove.alpha = alpha;
										}
									}
								
								/*Calculate value of move from [j][i] to [y][x] with your functions*/

							} else {
								continue;
							}
	
						}
					}
				} else {
					continue;
				}
				
			} else {
				continue;
			}
		}
	}

	return bestMove;
}

int maxMove(int alpha, int beta, int depthLeft, s_Node* Node)
{
	int value;
	t_coords coord1, coord2;

	int i,j,x,y;
	int legal[8][8];

	if(depthLeft == 0)
		return Node->pointTotal;

	for (i = 0; i < 8; i++) 
	{
		for (j = 0; j < 8; j++) {
			if (Node->board[j][i]) {
				if (Node->board[j][i]->team == Node->turn) 
				{
					coord1.locX = i;
					coord1.locY = j;
														
					genLegal(coord1, Node->board, legal);
				
					for (y = 0; y < 8; y++) {
						for (x = 0; x < 8; x++) {
							if (legal[y][x]) 
							{
								 /*does not pass coordinates of the current location*/
									coord2.locY = y;
									coord2.locX = x;
									
									addMove(Node, 0, coord1, coord2);
									value = minMove(alpha, beta, depthLeft-1, Node->down);
									murderChild(Node);

									if(value >= beta)
										return beta;
									if(value > alpha)
										alpha = value;
								
								/*Calculate value of move from [j][i] to [y][x] with your functions*/

							} else {
								continue;
							}
	
						}
					}
				} else {
					continue;
				}
				
			} else {
				continue;
			}
		}
	}

	return alpha;
	
}

int minMove(int alpha, int beta, int depthLeft, s_Node* Node)
{
	int value;
	t_coords coord1, coord2;

	int i,j,x,y;
	int legal[8][8];

	if(depthLeft == 0)
		return Node->pointTotal;

	for (i = 0; i < 8; i++) 
	{
		for (j = 0; j < 8; j++) {
			if (Node->board[j][i]) {
				if (Node->board[j][i]->team == Node->turn) 
				{
					coord1.locX = i;
					coord1.locY = j;
														
					genLegal(coord1, Node->board, legal);
				
					for (y = 0; y < 8; y++) {
						for (x = 0; x < 8; x++) {
							if (legal[y][x]) 
							{
																	coord2.locY = y;
									coord2.locX = x;
									
									addMove(Node, 1, coord1, coord2);
									value = maxMove(alpha, beta, depthLeft-1, Node->down);
									murderChild(Node);

									if(value <= alpha)
										return alpha;
									if(value < beta)
										beta = value;
								
								/*Calculate value of move from [j][i] to [y][x] with your functions*/
							} else {
								continue;
							}
	
						}
					}
				} else {
					continue;
				}
				
			} else {
				continue;
			}
		}
	}

	return beta;
}

