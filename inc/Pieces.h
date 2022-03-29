/*
 * Team 2 / Milk N Dim Sum
 * Pieces.h
 */

/*************************************** Notes **********************************************
 * 1/17/2014 - Bruce Liu - Created module and defined enums and structures. Also created 
 * 		basic functions.
 * 
 * *********************************** End Notes ********************************************/

#ifndef PIECES_H
#define PIECES_H

#include <stdlib.h>

typedef enum{
  
  WHITE, BLACK
  
}t_player;

typedef enum{
  
  KING   = 1000,
  QUEEN  = 88,
  ROOK   = 51,
  BISHOP = 33,
  KNIGHT = 32,
  PAWN   = 10
  
}t_piecetype;

typedef struct{
  
  int locY;
  int locX;
  
}t_coords;

typedef struct{
  
  t_player team;
  t_piecetype points;
  
}t_piece;

/*Initialize Piece*/
void initPiece(t_piece *p, t_player tm, t_piecetype pnt);

/* Get team color */
t_player getTeam(t_piece *piece);

/* Get piecetype */
t_piecetype getPieceType(t_piece *piece);

#endif /* PIECES_H */
