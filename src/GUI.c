/* GUI.c
 * Created by: Bruce Liu */

#include "../inc/GUI.h"


/* Initialized window and video mode */
/* Returns 1 if unsuccessful and 0 if successful */
int initVideo(char* title){
  
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
	printf("Unable to initialize SDL: %s\n", SDL_GetError());
	return 1;
  }
  atexit(SDL_Quit);
  
  SDL_WM_SetCaption(title, NULL);
  
  return 0;
  
}

/* loads an image and returns a pointer to the surface with the proper video initializations */
/* will return NULL if file could not be opened */
SDL_Surface *loadImage(char* filename, t_imgtype isSprite){
  
  int colorkey = 0;
  
  SDL_Surface *loadedImage = NULL;
  SDL_Surface *optimizedImage = NULL;
  
  /* load image */
  loadedImage = SDL_LoadBMP(filename);
  
  /* If the image loads, then optimize it */
  if(loadedImage != NULL){
	
	/* Optimize image to video mode settings */
	optimizedImage = SDL_DisplayFormat(loadedImage);
	
	/* free the old image */
	SDL_FreeSurface(loadedImage);
	
	/* Check to make sure DisplayFormat formatted the image correctly */
	if(optimizedImage != NULL && isSprite){
	  
	  /* map color key */
	  colorkey = SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF);
	  
	  /* Set pixels with RGB values of (0, 0xFF, 0xFF)(cyan) to be transparent */
	  SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	  
	}
	
	/* optimized image is returned */
	return optimizedImage;
	
  }
  else{
    
	printf("Could not open image: %s\n", SDL_GetError());
	return NULL;
  }
  
  
  
}

/* Applies the full size of source surface to destination surface */
void applySurface(SDL_Surface* source, SDL_Rect* clip, SDL_Surface* destination, int x, int y){
  
  assert(source);
  /* Create SDL_Rect structure which will used for blit'ing the surface */
  SDL_Rect offset;
  
  /* Now set int's x and y to offset structure variables */
  offset.x = x;
  offset.y = y;
  
  /* Blit the surface */
  SDL_BlitSurface(source, clip, destination, &offset);
  
}

/* Initialize an SDL_Rect [][] 2D array based on parameters */
void initRect(SDL_Rect clip[SPRITE_MAX][SPRITE_MAX], int sizeX, int sizeY, int rows, int cols){
  
  int i, j;
  for(j=0; j<rows; j++){
	for(i=0; i<cols; i++){
	  
	    clip[j][i].x = i*sizeX;
	    clip[j][i].y = j*sizeY;
	    clip[j][i].w = sizeX;
	    clip[j][i].h = sizeY;
	  
	}
  }
  
}

/* Displays initial main screen */
void applyMainScreen(SDL_Surface *screen, SDL_Surface *background, SDL_Surface *buttons, SDL_Surface *title, 
		     SDL_Rect buttonsFrame[SPRITE_MAX][SPRITE_MAX]){
  
  applySurface(background, NULL, screen, 0, 0);
  applySurface(title, NULL, screen, 55, 50);
  applySurface(buttons, &buttonsFrame[0][0], screen, 319, 210);
  applySurface(buttons, &buttonsFrame[1][0], screen, 319, 280);
  applySurface(buttons, &buttonsFrame[2][0], screen, 319, 350);
  applySurface(buttons, &buttonsFrame[8][0], screen, 319, 420);
  applySurface(buttons, &buttonsFrame[7][0], screen, 319, 490);
  
}

/* Displays initial Select Team Menu */
void applySelectTeam(SDL_Surface *screen, SDL_Surface *background, SDL_Surface *buttons2, SDL_Surface *title, 
		     SDL_Rect buttonsFrame[SPRITE_MAX][SPRITE_MAX]){
  
  applySurface(background, NULL, screen, 0, 0);
  applySurface(title, NULL, screen, 55, 50);
  applySurface(buttons2, &buttonsFrame[0][0], screen, 319, 280);
  applySurface(buttons2, &buttonsFrame[1][0], screen, 319, 420);
  
}

/* Displays initial option for custom or normal game */
void applySelectGame(SDL_Surface *screen, SDL_Surface *background, SDL_Surface *buttons, SDL_Surface *buttons2, SDL_Surface *title, 
		     SDL_Rect buttonsFrame[SPRITE_MAX][SPRITE_MAX]){
  
  applySurface(background, NULL, screen, 0, 0);
  applySurface(title, NULL, screen, 55, 50);
  applySurface(buttons2, &buttonsFrame[2][0], screen, 319, 280);
  applySurface(buttons, &buttonsFrame[4][0], screen, 319, 420);
  
}

/* Displays initial custom game setup screen */
void applyCustomScreen(SDL_Surface *screen, SDL_Surface *background, SDL_Surface *buttons2, SDL_Surface *pieces_white, SDL_Surface *pieces_black, 
		       SDL_Rect buttonsFrame[SPRITE_MAX][SPRITE_MAX], SDL_Rect piecesFrame[SPRITE_MAX][SPRITE_MAX]){
  
  applySurface(background, NULL, screen, 0, 0);
  
  applySurface(pieces_black, &piecesFrame[0][0], screen, 25, 20);
  applySurface(pieces_black, &piecesFrame[1][0], screen, 25, 100);
  applySurface(pieces_black, &piecesFrame[2][0], screen, 25, 180);
  applySurface(pieces_black, &piecesFrame[3][0], screen, 25, 260);
  applySurface(pieces_black, &piecesFrame[4][0], screen, 25, 340);
  applySurface(pieces_black, &piecesFrame[5][0], screen, 25, 420);
  
  applySurface(pieces_white, &piecesFrame[0][0], screen, 115, 20);
  applySurface(pieces_white, &piecesFrame[1][0], screen, 115, 100);
  applySurface(pieces_white, &piecesFrame[2][0], screen, 115, 180);
  applySurface(pieces_white, &piecesFrame[3][0], screen, 115, 260);
  applySurface(pieces_white, &piecesFrame[4][0], screen, 115, 340);
  applySurface(pieces_white, &piecesFrame[5][0], screen, 115, 420);
  
  applySurface(buttons2, &buttonsFrame[3][0], screen, 19, 500);
  
}

/* Displays initial gameboard WITHOUT pieces */
void applyGameScreen(SDL_Surface *screen, SDL_Surface *background, SDL_Surface *buttons, 
		     SDL_Rect buttonsFrame[SPRITE_MAX][SPRITE_MAX]){
  
  applySurface(background, NULL, screen, 0, 0);
  
  applySurface(buttons, &buttonsFrame[3][0], screen, 19, 160);
  applySurface(buttons, &buttonsFrame[5][0], screen, 19, 270);
  applySurface(buttons, &buttonsFrame[6][0], screen, 19, 380);
  
}

/* Sets locations for all buttons on current screen */
void setButtonLocs(t_screenItem buttonLocs[BUTTON_MAX]){
  
    /* PVP */
    buttonLocs[1].x = 319;  buttonLocs[1].y = 210;
    /* PVC */
    buttonLocs[2].x = 319;  buttonLocs[2].y = 280;
    /* Load */
    buttonLocs[3].x = 319;  buttonLocs[3].y = 350;
    /* Credits */
    buttonLocs[4].x = 319;  buttonLocs[4].y = 420;
    /* Quit */
    buttonLocs[5].x = 319;  buttonLocs[5].y = 490;
    /* Normal */
    buttonLocs[6].x = 319;  buttonLocs[6].y = 280;
    /* Custom */
    buttonLocs[7].x = 319;  buttonLocs[7].y = 420;
    /* Black */
    buttonLocs[8].x = 319;  buttonLocs[8].y = 280;
    /* White */
    buttonLocs[9].x = 319;  buttonLocs[9].y = 420;
    /* Start */
    buttonLocs[10].x = 19;   buttonLocs[10].y = 500;
    /* Save */
    buttonLocs[11].x = 19;   buttonLocs[11].y = 160;
    /* Undo */
    buttonLocs[12].x = 19;   buttonLocs[12].y = 270;
    /* End */
    buttonLocs[13].x = 19;   buttonLocs[13].y = 380;

}

/* Evaluates button for appropriate actions */
/* returns # if action is required */
/* modifies current screen if necessary */
int evalButton(t_screenType *currentScreen, int x, int y, t_screenItem buttonLocs[BUTTON_MAX], t_mouseCond* clicked, int *quit){
  
  switch(*currentScreen){
      
    case MAINSCREEN:
	if((x>buttonLocs[1].x) && (x<buttonLocs[1].x + BUTTON_WIDTH) && (y>buttonLocs[1].y)&&(y<buttonLocs[1].y+BUTTON_HEIGHT)){
	  if(*clicked == MOUSEUP){
	    *currentScreen = SELECTGAME;
	  }
	  else{
	    *clicked = MOUSEOVER;
	  }
	  
	  return 1;
	  
	}
	else if((x>buttonLocs[2].x) && (x<buttonLocs[2].x + BUTTON_WIDTH) && (y>buttonLocs[2].y)&&(y<buttonLocs[2].y+BUTTON_HEIGHT)){
	  if(*clicked == MOUSEUP){
	    *currentScreen = SELECTGAME;
	  }
	  else{
	    *clicked = MOUSEOVER;
	  }
	  return 2;
	  
	}
	else if((x>buttonLocs[3].x) && (x<buttonLocs[3].x + BUTTON_WIDTH) && (y>buttonLocs[3].y)&&(y<buttonLocs[3].y+BUTTON_HEIGHT)){
	  /* FIXME */
	  *clicked = MOUSEOVER;
	  return 3;
	  
	}
	else if((x>buttonLocs[4].x) && (x<buttonLocs[4].x + BUTTON_WIDTH) && (y>buttonLocs[4].y)&&(y<buttonLocs[4].y+BUTTON_HEIGHT)){
	  /* FIXME */
	  *clicked = MOUSEOVER;
	  return 4;
	  
	}
	else if((x>buttonLocs[5].x) && (x<buttonLocs[5].x + BUTTON_WIDTH) && (y>buttonLocs[5].y)&&(y<buttonLocs[5].y+BUTTON_HEIGHT)){
	  if(*clicked == MOUSEUP){
	    *quit = 1;
	  }
	  else{
	    *clicked = MOUSEOVER;
	  }
	  return 5;
	  
	}
	else {
	  return 0;
	}
	break;
    case SELECTGAME:
	if((x>buttonLocs[6].x) && (x<buttonLocs[6].x + BUTTON_WIDTH) && (y>buttonLocs[6].y)&&(y<buttonLocs[6].y+BUTTON_HEIGHT)){
	  if(*clicked == MOUSEUP){
	    *currentScreen = SELECTTEAM;
	  }
	  else{
	    *clicked = MOUSEOVER;
	  }
	  return 6;
	  
	}
	else if((x>buttonLocs[7].x) && (x<buttonLocs[7].x + BUTTON_WIDTH) && (y>buttonLocs[7].y)&&(y<buttonLocs[7].y+BUTTON_HEIGHT)){
	  if(*clicked == MOUSEUP){
	    *currentScreen = CUSTSCREEN;
	  }
	  else{
	    *clicked = MOUSEOVER;
	  }
	  return 7;
	  
	}
	else {
	  return 0;
	}
	break;
    case SELECTTEAM:
	if((x>buttonLocs[8].x) && (x<buttonLocs[8].x + BUTTON_WIDTH) && (y>buttonLocs[8].y)&&(y<buttonLocs[8].y+BUTTON_HEIGHT)){
	  if(*clicked == MOUSEUP){
	    *currentScreen = GAMESCREEN;
	  }
	  else{
	    *clicked = MOUSEOVER;
	  }
	  return 8;
	  
	}
	else if((x>buttonLocs[9].x) && (x<buttonLocs[9].x + BUTTON_WIDTH) && (y>buttonLocs[9].y)&&(y<buttonLocs[9].y+BUTTON_HEIGHT)){
	  if(*clicked == MOUSEUP){
	    *currentScreen = GAMESCREEN;
	  }
	  else{
	    *clicked = MOUSEOVER;
	  }
	  return 9;
	  
	}
	else {
	  return 0;
	}
	break;
    case CUSTSCREEN:
	if((x>buttonLocs[10].x) && (x<buttonLocs[10].x + BUTTON_WIDTH) && (y>buttonLocs[10].y)&&(y<buttonLocs[10].y+BUTTON_HEIGHT)){
	  if(*clicked == MOUSEUP){
	    *currentScreen = SELECTTEAM;
	  }
	  else{
	    *clicked = MOUSEOVER;
	  }
	  return 10;
	  
	}
	else {
	  return 0;
	}
	break;
    case GAMESCREEN:
	if((x>buttonLocs[11].x) && (x<buttonLocs[11].x + BUTTON_WIDTH) && (y>buttonLocs[11].y)&&(y<buttonLocs[11].y+BUTTON_HEIGHT)){
	  /* FIXME */
	  *clicked = MOUSEOVER;
	  return 11;
	  
	}
	else if((x>buttonLocs[12].x) && (x<buttonLocs[12].x + BUTTON_WIDTH) && (y>buttonLocs[12].y)&&(y<buttonLocs[12].y+BUTTON_HEIGHT)){
	  /* FIXME */
	  *clicked = MOUSEOVER;
	  return 12;
	  
	}
	else if((x>buttonLocs[13].x) && (x<buttonLocs[13].x + BUTTON_WIDTH) && (y>buttonLocs[13].y)&&(y<buttonLocs[13].y+BUTTON_HEIGHT)){
	  if(*clicked == MOUSEUP){
	    *currentScreen = MAINSCREEN;
	  }
	  else{
	    *clicked = MOUSEOVER;
	  }
	  return 13;
	  
	}
	else {
	  return 0;
	}
	break;
	
    default:
	return 0; /* should not be possible */
	break;
	
  }
}

/* redraws the select button */
void reButton(t_mouseCond clicked, t_screenItem buttonLocs[BUTTON_MAX], int redraw, SDL_Surface *screen, SDL_Surface *buttons, SDL_Surface *buttons2, 
	      SDL_Rect buttonsFrame[SPRITE_MAX][SPRITE_MAX]){
  if(clicked == MOUSEUP){
    clicked = MOUSEOVER;
  }
  switch(redraw){
    case 1: /* PvP */
      applySurface(buttons, &buttonsFrame[0][clicked], screen, buttonLocs[redraw].x, buttonLocs[redraw].y);
      break;
    case 2: /* PvC */
      applySurface(buttons, &buttonsFrame[1][clicked], screen, buttonLocs[redraw].x, buttonLocs[redraw].y);
      break;
    case 3: /* Load */
      applySurface(buttons, &buttonsFrame[2][clicked], screen, buttonLocs[redraw].x, buttonLocs[redraw].y);
      break;
    case 4: /* Credits */
      applySurface(buttons, &buttonsFrame[8][clicked], screen, buttonLocs[redraw].x, buttonLocs[redraw].y);
      break;
    case 5: /* Quit */
      applySurface(buttons, &buttonsFrame[7][clicked], screen, buttonLocs[redraw].x, buttonLocs[redraw].y);
      break;
    case 6: /* Normal */
      applySurface(buttons2, &buttonsFrame[2][clicked], screen, buttonLocs[redraw].x, buttonLocs[redraw].y);
      break;
    case 7: /* Custom */
      applySurface(buttons, &buttonsFrame[4][clicked], screen, buttonLocs[redraw].x, buttonLocs[redraw].y);
      break;
    case 8: /* Black */
      applySurface(buttons2, &buttonsFrame[0][clicked], screen, buttonLocs[redraw].x, buttonLocs[redraw].y);
      break;
    case 9: /* White */
      applySurface(buttons2, &buttonsFrame[1][clicked], screen, buttonLocs[redraw].x, buttonLocs[redraw].y);
      break;
    case 10: /* Start */
      applySurface(buttons2, &buttonsFrame[3][clicked], screen, buttonLocs[redraw].x, buttonLocs[redraw].y);
      break;
    case 11: /* Save */
      applySurface(buttons, &buttonsFrame[3][clicked], screen, buttonLocs[redraw].x, buttonLocs[redraw].y);
      break;
    case 12: /* Undo */
      applySurface(buttons, &buttonsFrame[5][clicked], screen, buttonLocs[redraw].x, buttonLocs[redraw].y);
      break;
    case 13: /* End */
      applySurface(buttons, &buttonsFrame[6][clicked], screen, buttonLocs[redraw].x, buttonLocs[redraw].y);
      break; 
  }
  
  
}

/* initialized a base board with no pieces */
void applyEmptyBoard(SDL_Surface *screen, SDL_Surface *blackSquare, SDL_Surface *whiteSquare){
  
  int i, j;
  
  for(j=0; j<8; j++){
    for(i=0; i<8; i++){
	if(j%2 == 0){
	  
	  if(i%2 == 0){
	      applySurface(whiteSquare, NULL, screen, BOARD_XOFFSET + i*SQUARE, BOARD_YOFFSET + j*SQUARE);
	  }
	  else if(i%2 == 1){
	      applySurface(blackSquare, NULL, screen, BOARD_XOFFSET + i*SQUARE, BOARD_YOFFSET + j*SQUARE);
	  }
	  
	}
	else if(j%2==1){
	  
	  if(i%2 == 0){
	      applySurface(blackSquare, NULL, screen, BOARD_XOFFSET + i*SQUARE, BOARD_YOFFSET + j*SQUARE);
	  }
	  else if(i%2 == 1){
	      applySurface(whiteSquare, NULL, screen, BOARD_XOFFSET + i*SQUARE, BOARD_YOFFSET + j*SQUARE);
	  }
	  
	}
    }
  }
  
}

/* Set board locations */
void setChessSquares(t_screenItem boardSqrs[BOARD_DIM][BOARD_DIM]){
  
  int i, j;
  
  for(j=0; j<8; j++){
    for(i=0; i<8; i++){
      
     boardSqrs[j][i].x = BOARD_XOFFSET + i*SQUARE;
     boardSqrs[j][i].y = BOARD_YOFFSET + j*SQUARE;
      
    }
  }
  
}

/* Set custom menu sprite highlighting locations */
void setCustSquares(t_screenItem customSqrs[BOARD_DIM][BOARD_DIM]){
  
  int i, j;
  
  for(j=0; j<6; j++){
    for(i=0; i<2; i++){
	
	customSqrs[j][i].x = 20 + i*90;
	customSqrs[j][i].y = 20 + j*80;
	
    }
    
  }
  
}

/* Evaluates for appropriate button actions */
/* updates highlighter */
/* returns select value int */
void evalSquares(t_screenType currentScreen, int x, int y, t_screenItem squares[BOARD_DIM][BOARD_DIM], t_screenItem customSqrs[BOARD_DIM][BOARD_DIM], t_screenItem *highlighter, t_screenItem *permHili, t_mouseCond *clicked, SDL_Surface *screen, SDL_Surface *hiliSquare, int *select, t_coords *from, t_coords *to, t_piecetype *assign, t_player *newteam){
  
  int i, j;
  switch(currentScreen){
    case CUSTSCREEN:
      for(j=0; j<6; j++){
	for(i=0; i<2; i++){
	    if((x>customSqrs[j][i].x) && (x<customSqrs[j][i].x + SQUARE) && (y>customSqrs[j][i].y)&&(y<customSqrs[j][i].y+SQUARE)){
		highlighter->x = customSqrs[j][i].x;
		highlighter->y = customSqrs[j][i].y;
		applySurface(hiliSquare, NULL, screen, highlighter->x, highlighter->y);
		if(*clicked == MOUSEUP){
		    t_piecetype alltypes[6];
		    alltypes[0] = KING;
		    alltypes[1] = QUEEN;
		    alltypes[2] = BISHOP;
		    alltypes[3] = KNIGHT;
		    alltypes[4] = ROOK;
		    alltypes[5] = PAWN;
		    permHili->x = highlighter->x;
		    permHili->y = highlighter->y;
		    *assign = alltypes[j];
		    if(i==0){
		      *newteam = 1;
		    }
		    else{
		      *newteam = 0;
		    }
		    *select = 1;
		}
		  
		/* exit loops */
		j = 6;
		i = 2;
	    }
	}
      }
      if((x > BOARD_XOFFSET) && (x < BOARD_XOFFSET + 560) && (y > BOARD_YOFFSET) && (y < BOARD_YOFFSET + 560)){
	  i = (x - BOARD_XOFFSET) / SQUARE;
	  j = (y - BOARD_YOFFSET) / SQUARE;
	  
	  highlighter->x = squares[j][i].x;
	  highlighter->y = squares[j][i].y;
	  if(*clicked == MOUSEUP){
	    if(*select = 1){
	      /* Use to coords to assign piece to square */
	      to->locX = i;
	      to->locY = 7-j;
	      *select = 2;
	    }
	  }
	  else{
	    *clicked = MOUSEOVER;
	  }
	  applySurface(hiliSquare, NULL, screen, highlighter->x, highlighter->y);
      }
      break;
    case GAMESCREEN:
      
      if((x > BOARD_XOFFSET) && (x < BOARD_XOFFSET + 560) && (y > BOARD_YOFFSET) && (y < BOARD_YOFFSET + 560)){
	  i = (x - BOARD_XOFFSET) / SQUARE;
	  j = (y - BOARD_YOFFSET) / SQUARE;
	  
	  highlighter->x = squares[j][i].x;
	  highlighter->y = squares[j][i].y;
	  applySurface(hiliSquare, NULL, screen, highlighter->x, highlighter->y);
	  if(*clicked == MOUSEUP){
	      if(*select == 0){
		  permHili->x = highlighter->x;
		  permHili->y = highlighter->y;
		  from->locX = i;
		  from->locY = 7-j;
		  printf("Got from coords!\n"
			 "from->locX:    %d\n"
			 "from->locY:    %d\n", from->locX, from->locY);
		  *select = 1;
	      }
	      else if(*select == 1){
		  to->locX = i;
		  to->locY = 7-j;
		  printf("Got to coords!\n"
			 "to->locX:    %d\n"
			 "to->locY:    %d\n", to->locX, to->locY);
		  *select = 2;
	      }
	  }
	  else{
	    *clicked = MOUSEOVER;
	  }
      }
      
      
      break;
      
    default: /* Not possible unless used outside these two cases */
      break;
    
  }
  
}

/* Draws the highlighting of squares */
/* Used in evalSquares only! */
void reSquare(t_screenType currentScreen, t_screenItem highlighter, t_mouseCond clicked, SDL_Surface *screen, SDL_Surface *hiliSquare){
  
  if(clicked == MOUSEUP){
    applySurface(hiliSquare, NULL, screen, highlighter.x, highlighter.y);
    /* FIXME */
  }
  else if(clicked == MOUSEOVER){
    applySurface(hiliSquare, NULL, screen, highlighter.x, highlighter.y);
  }
  
}

/* display board pieces */
void displayPieces(t_piece *gameboard[8][8], t_screenItem boardSqrs[BOARD_DIM][BOARD_DIM], SDL_Surface *screen, SDL_Surface *pieces_black, SDL_Surface *pieces_white, SDL_Rect piecesFrame[SPRITE_MAX][SPRITE_MAX]){
  
  int i, j;
  
  for(j=0; j<BOARD_DIM; j++){
    for(i=0; i<BOARD_DIM; i++){
      if(gameboard[7-j][i] != NULL){
	switch(gameboard[7-j][i]->points){
	  case KING:
	    if(gameboard[7-j][i]->team == BLACK){
	      applySurface(pieces_black, &piecesFrame[0][0], screen, boardSqrs[j][i].x + SPRITE_XOFFSET, boardSqrs[j][i].y);
	    }
	    else{
	      applySurface(pieces_white, &piecesFrame[0][0], screen, boardSqrs[j][i].x + SPRITE_XOFFSET, boardSqrs[j][i].y);
	    }
	    break;
	  case QUEEN:
	    if(gameboard[7-j][i]->team == BLACK){
	      applySurface(pieces_black, &piecesFrame[1][0], screen, boardSqrs[j][i].x + SPRITE_XOFFSET, boardSqrs[j][i].y);
	    }
	    else{
	      applySurface(pieces_white, &piecesFrame[1][0], screen, boardSqrs[j][i].x + SPRITE_XOFFSET, boardSqrs[j][i].y);
	    }
	    break;
	  case BISHOP:
	    if(gameboard[7-j][i]->team == BLACK){
	      applySurface(pieces_black, &piecesFrame[2][0], screen, boardSqrs[j][i].x + SPRITE_XOFFSET, boardSqrs[j][i].y);
	    }
	    else{
	      applySurface(pieces_white, &piecesFrame[2][0], screen, boardSqrs[j][i].x + SPRITE_XOFFSET, boardSqrs[j][i].y);
	    }
	    break;
	  case KNIGHT:
	    if(gameboard[7-j][i]->team == BLACK){
	      applySurface(pieces_black, &piecesFrame[3][0], screen, boardSqrs[j][i].x + SPRITE_XOFFSET, boardSqrs[j][i].y);
	    }
	    else{
	      applySurface(pieces_white, &piecesFrame[3][0], screen, boardSqrs[j][i].x + SPRITE_XOFFSET, boardSqrs[j][i].y);
	    }
	    break;
	  case ROOK:
	    if(gameboard[7-j][i]->team == BLACK){
	      applySurface(pieces_black, &piecesFrame[4][0], screen, boardSqrs[j][i].x + SPRITE_XOFFSET, boardSqrs[j][i].y);
	    }
	    else{
	      applySurface(pieces_white, &piecesFrame[4][0], screen, boardSqrs[j][i].x + SPRITE_XOFFSET, boardSqrs[j][i].y);
	    }
	    break;
	  case PAWN:
	    if(gameboard[7-j][i]->team == BLACK){
	      applySurface(pieces_black, &piecesFrame[5][0], screen, boardSqrs[j][i].x + SPRITE_XOFFSET, boardSqrs[j][i].y);
	    }
	    else{
	      applySurface(pieces_white, &piecesFrame[5][0], screen, boardSqrs[j][i].x + SPRITE_XOFFSET, boardSqrs[j][i].y);
	    }
	    break;
	  default: /* shouldn't happen */
	    break;
	}
      }
    }
  }
  
}
