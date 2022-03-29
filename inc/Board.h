/*
 * Team 2 / Milk N Dim Sum
 * Board.h
 */

/*************************************** Notes **********************************************
 * 1/17/2014 - Bruce Liu - Created module and declared basic functions.
 * 
 * *********************************** End Notes ********************************************/

#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>
#include "../inc/Pieces.h"
#include "../inc/IO.h"



/* initializes board to all NULL */
void initBoard(t_piece *board[8][8], t_piece* pieces[12]);

/*Copies one board to another board array (used much in AI)*/
void copyBoard(t_piece *oldBoard[8][8], t_piece *newBoard[8][8]);

/*initializes board with no peices*/
void initBlankBoard(t_piece *board[8][8]);

/*add single piece to board */
void addPiece(t_piece *board[8][8], t_piecetype type, t_player team, t_coords position);

/*allows user to set up a custom board*/
void SetCustomBoard(t_piece *GameBoard[8][8]);
#endif /* BOARD_H */
