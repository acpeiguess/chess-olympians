/* GUI.h
 * SDL Test of all SDL functions in separate module */

#ifndef GUI_H
#define GUI_H

#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "assert.h"
#include "Pieces.h"

#define W_WIDTH 800
#define W_HEIGHT 600
#define C_DEPTH 32
#define SQUARE 70
#define SPRITE_WIDTH 60
#define SPRITE_HEIGHT 70
#define SPRITE_MAX 20   /* Maximum of 20x20 divisions for any sprite surface */
#define SPRITE_XOFFSET 5
#define SPRITE_YOFFSET 0
#define BOARD_XOFFSET 230
#define BOARD_YOFFSET 10
#define BOARD_DIM 8
#define BUTTON_WIDTH 162
#define BUTTON_HEIGHT 60
#define BUTTON_MAX 20


/* Used to determine if a image needs color key transparency */
typedef enum{
  
  BKGRND = 0,
  SPRITE = 1
  
}t_imgtype;

/* Used to set current button sprite */
typedef enum{
  
  MOUSEOUT = 0,
  MOUSEOVER = 1,
  MOUSEDOWN = 2,
  MOUSEUP = 3
  
}t_mouseCond;

typedef enum{
  
  MAINSCREEN = 0,
  SELECTGAME = 1,
  SELECTTEAM = 2,
  CUSTSCREEN = 3,
  GAMESCREEN = 4
  
}t_screenType;

/* Used to set a reference to an item's position */
typedef struct{
  
  int x;
  int y;
  
}t_screenItem;


/* Initialized window and video mode */
/* Returns 1 if unsuccessful and 0 if successful */
int initVideo(char* title);

/* loads an image and returns a pointer to the surface with the proper video initializations */
/* will return NULL if file could not be opened */
SDL_Surface *loadImage(char* filename, t_imgtype isSprite);

/* Applies the full size of source surface to destination surface */
void applySurface(SDL_Surface *source, SDL_Rect* clip, SDL_Surface *destination, int x, int y);

/* Initialize an SDL_Rect [][] 2D array based on parameters */
void initRect(SDL_Rect clip[SPRITE_MAX][SPRITE_MAX], int sizeX, int sizeY, int rows, int cols);

/* Displays initial main screen */
void applyMainScreen(SDL_Surface *screen, SDL_Surface *background, SDL_Surface *buttons, SDL_Surface *title, 
		     SDL_Rect buttonsFrame[SPRITE_MAX][SPRITE_MAX]);

/* Displays initial Select Team Menu */
void applySelectTeam(SDL_Surface *screen, SDL_Surface *background, SDL_Surface *buttons2, SDL_Surface *title, 
		     SDL_Rect buttonsFrame[SPRITE_MAX][SPRITE_MAX]);

/* Displays initial option for custom or normal game */
void applySelectGame(SDL_Surface *screen, SDL_Surface *background, SDL_Surface *buttons, SDL_Surface *buttons2, SDL_Surface *title, 
		     SDL_Rect buttonsFrame[SPRITE_MAX][SPRITE_MAX]);

/* Displays initial custom game setup screen */
void applyCustomScreen(SDL_Surface *screen, SDL_Surface *background, SDL_Surface *buttons2, SDL_Surface *pieces_white, SDL_Surface *pieces_black, 
		       SDL_Rect buttonsFrame[SPRITE_MAX][SPRITE_MAX], SDL_Rect piecesFrame[SPRITE_MAX][SPRITE_MAX]);

/* Displays initial gameboard WITHOUT pieces */
void applyGameScreen(SDL_Surface *screen, SDL_Surface *background, SDL_Surface *buttons, 
		     SDL_Rect buttonsFrame[SPRITE_MAX][SPRITE_MAX]);

/* Sets locations for all buttons */
void setButtonLocs(t_screenItem buttonLocs[BUTTON_MAX]);

/* Evaluates button for appropriate actions */
/* returns # if action is required */
/* modifies current screen and clicked if necessary */
int evalButton(t_screenType *currentScreen, int x, int y, t_screenItem buttonLocs[BUTTON_MAX], t_mouseCond* clicked, int *quit);

/* perform appropriate redraw */
void reButton(t_mouseCond clicked, t_screenItem buttonLocs[BUTTON_MAX], int redraw, SDL_Surface *screen, SDL_Surface *buttons, SDL_Surface *buttons2, 
	      SDL_Rect buttonsFrame[SPRITE_MAX][SPRITE_MAX]);

/* initialized a base board with no pieces */
void applyEmptyBoard(SDL_Surface *screen, SDL_Surface *blackSquare, SDL_Surface *whiteSquare);

/* Set board locations */
void setChessSquares(t_screenItem boardSqrs[BOARD_DIM][BOARD_DIM]);

/* Set custom menu sprite highlighting locations */
void setCustSquares(t_screenItem customSqrs[BOARD_DIM][BOARD_DIM]);

/* Evaluates for appropriate button actions */
/* returns select value int */
void evalSquares(t_screenType currentScreen, int x, int y, t_screenItem squares[BOARD_DIM][BOARD_DIM], t_screenItem customSqrs[BOARD_DIM][BOARD_DIM], t_screenItem *highlighter, t_screenItem *permHili, t_mouseCond *clicked, SDL_Surface *screen, SDL_Surface *hiliSquare, int *select, t_coords *from, t_coords *to, t_piecetype *assign, t_player *newteam);

/* Draws the highlighting of squares */
void reSquare(t_screenType currentScreen, t_screenItem highlighter, t_mouseCond clicked, SDL_Surface *screen, SDL_Surface *hiliSquare);

/* display board pieces */
void displayPieces(t_piece *gameboard[8][8], t_screenItem boardSqrs[BOARD_DIM][BOARD_DIM], SDL_Surface *screen, SDL_Surface *pieces_black, SDL_Surface *pieces_white, SDL_Rect piecesFrame[SPRITE_MAX][SPRITE_MAX]);

#endif /* GUI_H */ 
