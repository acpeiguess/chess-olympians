/*
 * Team 2 / Milk N Dim Sum
 * Pieces.c
 */

/*************************************** Notes **********************************************
 * 1/17/2014 - Bruce Liu - Created module and basic functions
 * 
 * *********************************** End Notes ********************************************/

#include "../inc/Pieces.h"

/*Initialize piece*/
void initPiece(t_piece *p, t_player tm, t_piecetype pnt){
  
  p->team = tm;
  p->points = pnt;
  
}


/* Get team color */
t_player getTeam(t_piece *piece){
  
  return piece->team;
  
}

/* Get piecetype */
t_piecetype getPieceType(t_piece *piece){
  
  return piece->points;
  
}
