#ifndef RULES_H
#define RULES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pieces.h"
#include "Board.h"

/*must return 1 or 0  if this grid contain the piece that is movable*/
int checkLoc (t_piece *GameBoard[8][8], int locY, int locX, int turn);
/*turn is either 1 or 0, 1 for white and 0 for black*/

/*must return 1 or 0 if the destination is legal to move*/
int checkLoc2 (t_coords *coords);

/*move the piece from loc1 to loc2 copy pointer from loc1 to loc 2 then set loc1 to null*/
int movePiece(t_piece *GameBoard[8][8], t_coords coords1,t_coords coords2);

/*This will generate a bit array of possible legal moves*/
void genLegal(t_coords coords, t_piece *GameBoard[8][8], int legal[8][8]);

void pawn(int locY, int locX, t_piece *GameBoard[8][8],int cteam,int legal[8][8]);

void bishop(int locY, int locX, t_piece *GameBoard[8][8],int cteam,int legal[8][8]);

void rook(int locY, int locX, t_piece *GameBoard[8][8],int cteam,int legal[8][8]);

void knight(int locY, int locX, t_piece *GameBoard[8][8],int cteam,int legal[8][8]);

void queen(int locY, int locX, t_piece *GameBoard[8][8],int cteam,int legal[8][8]);

void king(int locY, int locX, t_piece *GameBoard[8][8],int cteam,int legal[8][8]);

/* King has the ability of a queen and a knight */
/* Used for Check and Checkmate */
void superKing(t_piece *GameBoard[8][8], t_coords coords, int cteam, int kingarray[8][8]);

/* Checks for possible suicidal moves that the king should be prevented from doing */
void kingSuicide(t_piece *GameBoard[8][8], int legal[8][8], t_coords coords);

/* Checks if the king is "in check" */
int Check(t_piece *GameBoard[8][8], t_coords coords, int cteam);

/* Checks if there's a stalemate */
int Stalemate(t_piece* GameBoard[8][8], t_coords coords);

/*Checkmate check*/
int Checkmate(int kArray[8][8], t_piece* board[8][8], int cteam, int legal[8][8]);

/*used to import the pieces array from main used only once*/
void importPieces(t_piece *PIECES[12]);

#endif 
