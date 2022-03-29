/*
 * Team 2 / Milk N Dim Sum
 * IO.h
 */

/*************************************** Notes **********************************************
 * 1/17/2014 - Bruce Liu - Created module and declared basic print functions
 * 
 * *********************************** End Notes ********************************************/

#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pieces.h"
#include "Board.h"
#include "Rules.h"

/* Prints board */
void printBoard(t_piece* gameboard[8][8]);

/* returns string associated with piecetype */
char getPTypeChar( t_piece *piece);

/* returns string associated with team color */
char getPieceColorChar(t_piece *piece);

/* Prints Main Menu */
void printMainMenu();

/* Prints Game Menu */
void printGameMenu();

/* Get Integer */
int getInt(char* message);

/* Get Move */
void getMove(char* move);

/* Decode Move: will return 1 if valid coords are decoded. returns 0 if invalid move is decoded */
int decodeMove (char* move, t_coords *from, t_coords *to,  t_piece *board[8][8], int team);

/* Returns upper case char when lower/upper case char is given */
char toUpper(char letter);

/* verifies that value is within desired range of numbers */
int EnsureNumber(int value, int botRange, int topRange);

#endif /* IO_H */
