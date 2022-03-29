/*****************************************************************************************
 *Project: Chess Olympians (GUI Version)
 *Developer: Team 2 / Milk & Dim Sum
 *Description: A graphical program that allows the user
 *             to play chess against another user or
 *             against the computer
 * 
 *****************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "../inc/GUI.h"
#include "../inc/Pieces.h"
#include "../inc/IO.h"
#include "../inc/Board.h"
#include "../inc/Rules.h"
#include "../inc/AI.h"

/*********************** Prototypes ******************************/

void GameRecord(FILE* out, t_coords* c1, t_coords* c2, t_piece* GameBoard[8][8]);
void UndoMove(int undo[12], t_piece* board[8][8], t_piece* pieces[12], int* moveCnt);

/******************** End Prototypes *****************************/


int main(int argc, char* args[]){
  
  t_piece *board[8][8];
  t_piece* pieces[12];
  int ingame = 0;
  t_player team = BLACK;
  int WhiteAI = 0;
  int BlackAI = 0;
  t_coords from;
  t_coords to;
  FILE* gameLog;
  t_piecetype assign;
  t_player newteam;
  importPieces(pieces);
  int quit = 0;
  int PvP = 0;
  int mouseX = 0, mouseY = 0;
  int redrawButton = 0;
  int redrawPiece = 0;
  int gameSelect = 0;
  t_mouseCond clicked = 0;
  t_screenType currentScreen = MAINSCREEN;
  t_screenItem buttonLocs[BUTTON_MAX];
  t_screenItem boardSqrs[BOARD_DIM][BOARD_DIM];
  t_screenItem customSqrs[BOARD_DIM][BOARD_DIM];
  t_screenItem highlighter;
  t_screenItem permHili;
  
  /***************** Control flow initializations ****************/
  

   /*Set up game log*/
  gameLog = fopen("GameLog.txt", "w");
    if(!gameLog){
	printf("Could not open file for Log!\n");
    } else {
  fprintf(gameLog, "Team\tType\tFrom\tTo\tPiece Taken\n\n");
  }
  fclose(gameLog);
  int* moveCnt = malloc(sizeof(int));
  *moveCnt = 0;
  
  /************* END Control flow initializations ****************/
  
  /********************* SDL Initializations *********************/
  /* Set locations(permanent) */
  setButtonLocs(buttonLocs);
  setChessSquares(boardSqrs);
  setCustSquares(customSqrs);
  
  /* Surfaces */
  SDL_Surface *screen = NULL;
  SDL_Surface *background = NULL;
  SDL_Surface *title = NULL;
  SDL_Surface *blackSquare = NULL;
  SDL_Surface *whiteSquare = NULL;
  SDL_Surface *hiliSquare = NULL;
  SDL_Surface *pieces_white = NULL;
  SDL_Surface *pieces_black = NULL;
  SDL_Surface *buttons = NULL;
  SDL_Surface *buttons2 = NULL; /* You can use buttonsFrame Rect since buttons 2 is smaller */
  
  /* Coordinates for white and black sprite surface extraction */
  SDL_Rect piecesFrame[SPRITE_MAX][SPRITE_MAX];
  
  /* Coordinates for Buttons sprite surface extraction */
  SDL_Rect buttonsFrame[SPRITE_MAX][SPRITE_MAX];
  
  /* Event */
  SDL_Event event;
  
  /* Initialize piecesFrame */
  initRect(piecesFrame, SPRITE_WIDTH, SPRITE_HEIGHT, 6, 4);
  
  /* Initialize buttonsFrame */
  /* values were determined by image configuration */
  initRect(buttonsFrame, 162, 60, 9, 3);
  
  /* initialize video */
  if(initVideo("Chess Olympian")){
	return 1;
  }
  screen = SDL_SetVideoMode(W_WIDTH, W_HEIGHT, C_DEPTH, SDL_DOUBLEBUF | SDL_SWSURFACE);
  /* SDL_DOUBLEBUF make image rendering smooth.
   * Window vs Fullscreen: SDL_FULLSCREEN vs SDL_SWSURFACE 
   * SDL_SetVideoMode must be used in main otherwise screen will be null. I don't know why. */
  if (screen == NULL) {
	printf("Unable to set video mode: %s\n", SDL_GetError());
	return 1;
  }
  
  printf("Initialized screen!\n");
  
  /* Load all images to surfaces */
  background = loadImage("resources/background.bmp", BKGRND);
  blackSquare = loadImage("resources/black_sq.bmp", BKGRND);
  whiteSquare = loadImage("resources/white_sq.bmp", BKGRND);
  hiliSquare = loadImage("resources/highlight.bmp", SPRITE);
  pieces_white = loadImage("resources/Wh_Pieces.bmp", SPRITE);
  pieces_black = loadImage("resources/Bl_Pieces.bmp", SPRITE);
  buttons = loadImage("resources/buttons.bmp", SPRITE);
  buttons2 = loadImage("resources/buttons2.bmp", SPRITE);
  title = loadImage("resources/title.bmp", SPRITE);
  
  if(!background || !blackSquare || !whiteSquare || !pieces_white || !pieces_black || !buttons || !buttons2 || !title || !hiliSquare){
	return 1;
  }
  printf("Loaded all Images!\n");
  /********************* End SDL initializations ***************************/
  
  /********************** Program loop goes here ***************************/
  /* while not exiting condition */
  while(!quit){
#ifdef DEBUG
	printf("in 1st while loop\n");
#endif
	/* while there's an event to handle */
	while(SDL_PollEvent(&event)){
#ifdef DEBUG
	  printf("in 2nd while loop\n");
#endif
	  /* The user clicks x to close the program */
	  switch(event.type){
	    
	    case SDL_MOUSEMOTION: /* Mouse moved */
	      
	      mouseX = event.motion.x;
	      mouseY = event.motion.y;
	      clicked = MOUSEOUT;
	      
	      break;
	    case SDL_MOUSEBUTTONDOWN: /* Mouse button was pressed down */
	      if(event.button.button == SDL_BUTTON_LEFT){
		
		mouseX = event.button.x;
		mouseY = event.button.y;
		clicked = MOUSEDOWN;
		
	      }
	      break;
	    case SDL_MOUSEBUTTONUP: /* Mouse button was released from down pos */
	      if(event.button.button == SDL_BUTTON_LEFT){
		
		mouseX = event.button.x;
		mouseY = event.button.y;
		clicked = MOUSEUP;
		
	      }
	      break;
	    case SDL_QUIT: /* Program exits */
	      quit = 1;
	      break;
	    
	  } /*end switch */
	}/* end poll event while loop */
	
	switch(currentScreen){
	    
	    case MAINSCREEN:
	      applyMainScreen(screen, background, buttons, title, buttonsFrame);
	      redrawButton = evalButton(&currentScreen, mouseX, mouseY, buttonLocs, &clicked, &quit);
	      reButton(clicked, buttonLocs, redrawButton, screen, buttons, buttons2, buttonsFrame);
	      if((redrawButton == 1) && (clicked == MOUSEUP)){
		WhiteAI = 0;
		BlackAI = 0;
		PvP = 1;
	      }
	      else if((redrawButton == 2) && (clicked == MOUSEUP)){
		PvP = 0;
	      }
	      break;
	    case SELECTGAME:
	      applySelectGame(screen, background, buttons, buttons2, title, buttonsFrame);
	      redrawButton = evalButton(&currentScreen, mouseX, mouseY, buttonLocs, &clicked, &quit);
	      if((redrawButton == 6) && (clicked == MOUSEUP)){
		initBoard(board, pieces);
	      }
	      else if((redrawButton == 7) && (clicked == MOUSEUP)){
		initBlankBoard(board);
	      }
	      reButton(clicked, buttonLocs, redrawButton, screen, buttons, buttons2, buttonsFrame);
	      break;
	    case SELECTTEAM:
	      applySelectTeam(screen, background, buttons2, title, buttonsFrame);
	      redrawButton = evalButton(&currentScreen, mouseX, mouseY, buttonLocs, &clicked, &quit);
	      reButton(clicked, buttonLocs, redrawButton, screen, buttons, buttons2, buttonsFrame);
	      if((redrawButton == 8) && (clicked == MOUSEUP)){
		team = BLACK;
		if(!PvP){
		  BlackAI = 0;
		  WhiteAI = 1;
		}
		gameSelect = 0;
	      }
	      else if((redrawButton == 9) && (clicked == MOUSEUP)){
		team = WHITE;
		if(!PvP){
		  BlackAI = 1;
		  WhiteAI = 0;
		}
		gameSelect = 0;
	      }
	      
	      break;
	    case CUSTSCREEN:
	      applyCustomScreen(screen, background, buttons2, pieces_white, pieces_black, buttonsFrame, piecesFrame);
	      applyEmptyBoard(screen, blackSquare, whiteSquare);
	      displayPieces(board, boardSqrs, screen, pieces_black, pieces_white, piecesFrame);
	      redrawButton = evalButton(&currentScreen, mouseX, mouseY, buttonLocs, &clicked, &quit);
	      reButton(clicked, buttonLocs, redrawButton, screen, buttons, buttons2, buttonsFrame);
	      evalSquares(currentScreen, mouseX, mouseY, boardSqrs, customSqrs, &highlighter, &permHili, &clicked, screen, hiliSquare, &gameSelect, &from, &to, &assign, &newteam);
	      if(gameSelect == 1){
		
		applySurface(hiliSquare, NULL, screen, permHili.x, permHili.y);
		
	      }
	      else if(gameSelect == 2){
		
		addPiece(board, assign, newteam, to);
		gameSelect = 0;
	      }
	      
	      
	      /* FIXME */
	      
	      break;
	    case GAMESCREEN:
	      applyGameScreen(screen, background, buttons, buttonsFrame);
	      applyEmptyBoard(screen, blackSquare, whiteSquare);
	      displayPieces(board, boardSqrs, screen, pieces_black, pieces_white, piecesFrame);
	      redrawButton = evalButton(&currentScreen, mouseX, mouseY, buttonLocs, &clicked, &quit);
	      if((redrawButton == 11) && (clicked == MOUSEUP)){
		/* FIXME */
		/* no Save function yet */
	      }
	      else if((redrawButton == 12) && (clicked == MOUSEUP)){
		/* FIXME */
		/* Undo function gives segmentation fault */
	      }
	      reButton(clicked, buttonLocs, redrawButton, screen, buttons, buttons2, buttonsFrame);
	      evalSquares(currentScreen, mouseX, mouseY, boardSqrs, customSqrs, &highlighter, &permHili, &clicked, screen, hiliSquare, &gameSelect, &from, &to, &assign, &newteam);
	      
	      if(gameSelect == 1){
		
		applySurface(hiliSquare, NULL, screen, permHili.x, permHili.y);
		
	      }
	      else if(gameSelect == 2){
		GameRecord(gameLog, &from, &to, board);
		if (board[from.locY][from.locX]->points == KING) {
			printf("HERE\n");
			if (from.locX - to.locX == 2) {
				board[to.locY][3] = board[to.locY][0];
				board[to.locY][0] = NULL;
			}
			if (from.locX - to.locX == -2) {
				board[to.locY][5] = board[to.locY][7];
				board[to.locY][7] = NULL;
			}
		}
		 /* CHARLIE!!! OVER HERE */
		 /* In this condition, team is selected and from and to coords are set. */
		 /* Enter check moves here */
		if (checkLoc(board, from.locY, from.locX, team)&&checkLoc2(&to))
		{
		      movePiece(board, from,to);
		      if(team == WHITE){
			printf("Switching from white to black...\n");
			printf("BlackAI:    %d\n", BlackAI);
			if(BlackAI == 0){
			  team = BLACK;
			  printf("new team assign:    %d\n", team);
			}
		      }
		      else if(team == BLACK){
			printf("Switching from black to white...\n");
			printf("WhiteAI:    %d\n", WhiteAI);
			if(WhiteAI == 0){
			  team = WHITE;
			  printf("new team assign:    %d\n", team);
			}
		      }
		      if(BlackAI || WhiteAI){
			/* AI actions here */
			/*printf("Press enter to continue: ");
			getchar(); getchar();*/
			t_move aiMove = findBestMove(board, BLACK, DEPTH);
			
			GameRecord(gameLog, &(aiMove.pieceLoc), &(aiMove.pieceDest), board);
			
			movePiece(board, aiMove.pieceLoc, aiMove.pieceDest);
			/*printf("\n%d%d\n", aiMove.pieceLoc.locX, aiMove.pieceLoc.locY);*/
		      }
		}/*Piece is moved and team switched*/
		else
		{}/*END OF RULES IMPLEMENTAION*/
		gameSelect = 0;
	      }
	      
	      break;
	    
	} /* end switch */

    SDL_Flip(screen);
    SDL_Delay(150);
    clicked = MOUSEOUT;
        
  }/* end !quit while loop */
  
  /*************************************************************************/
  
  free(moveCnt);
  SDL_FreeSurface(blackSquare);
  SDL_FreeSurface(whiteSquare);
  SDL_FreeSurface(pieces_white);
  SDL_FreeSurface(pieces_black);
  SDL_FreeSurface(buttons);
  SDL_FreeSurface(buttons2);
  SDL_FreeSurface(title);
  SDL_FreeSurface(background);
  SDL_Quit();
  
  return 0;
}


/*********************** Functions ********************************/


void GameRecord(FILE* out, t_coords* c1, t_coords* c2, t_piece* GameBoard[8][8]) {
	char* type = malloc(sizeof(char));
	char* type1 = malloc(sizeof(char));
	char* team = malloc(sizeof(char));

	*type1 = getPTypeChar(GameBoard[c1->locY][c1->locX]);
	*team = getPieceColorChar(GameBoard[c1->locY][c1->locX]);
	*team -= 32;

	if (GameBoard[c2->locY][c2->locX]) {
		*type = getPTypeChar(GameBoard[c2->locY][c2->locX]);
	} else {
		*type = ' ';
	}
	out = fopen("GameLog.txt", "a");
		if(!out){
			printf("Could not open file for Log!\n");
    		} else {
		fprintf(out, "%c\t%c\t%c%d\t%c%d\t%c\n", *team, *type1, c1->locX + 65, c1->locY + 1, c2->locX + 65, c2->locY + 1, *type);
		fclose(out);
		}

	free(type);
	free(type1);
	free(team);
}

void UndoMove(int undo[12], t_piece* board[8][8], t_piece* pieces[12], int* moveCnt) {
if (*moveCnt>1) {
/*some initializations*/
	FILE* fpOld;
	FILE* fpNew;
	long location;
	char temp;
	int iter = 0;
	t_coords* from = malloc(sizeof(t_coords));
	t_coords* to = malloc(sizeof(t_coords));	

	fpOld = fopen("GameLog.txt", "r+");
	fpNew = fopen("NewLog.txt", "w");
	fseek(fpOld, (-24*sizeof(char)), SEEK_END);
	location = ftell(fpOld);
/*while loop iterates through the original file and copies all but the last two lines to a new file*/
	fseek(fpOld, 0, SEEK_SET);
	while (ftell(fpOld) != location) {
		temp = fgetc(fpOld);
		fputc(temp, fpNew);
	}
/*This loop loads an array with the contents of last two lines*/
	do {
		temp = fgetc(fpOld);
		undo[iter] = temp;
		iter++;
	} while(temp != EOF);

	remove("GameLog.txt");
	rename("NewLog.txt", "GameLog.txt");
	fclose(fpOld);
	fclose(fpNew);
/*for loop intended to first undo the latest move, then the intended move*/
/*places fallen pieces back on the board if necessary*/
	for (iter = 0; iter < 2; iter++) {
		if (board[(undo[20 - (iter*12)] - 49)][(undo[19 - (iter*12)] - 65)]) {
			to->locY = undo[17 - (iter*12)] - 49;
			to->locX = undo[16 - (iter*12)] - 65;
			from->locY = undo[20 - (iter*12)] - 49;
			from->locX = undo[19 - (iter*12)] - 65;
			movePiece(board, *from, *to);
			switch (undo[22 - (iter*12)]) {
				case 'P':
					if (undo[12 - (iter*12)] == 'W') {
					board[from->locY][from->locX] = pieces[0];
					} else {
					board[from->locY][from->locX] = pieces[6];
					}
					break;
				case 'N':
					if (undo[12 - (iter*12)] == 'W') {
					board[from->locY][from->locX] = pieces[1];
					} else {
					board[from->locY][from->locX] = pieces[7];
					}
					break;
				case 'B':
					if (undo[12 - (iter*12)] == 'W') {
					board[from->locY][from->locX] = pieces[2];
					} else {
					board[from->locY][from->locX] = pieces[8];
					}
					break;
				case 'R':
					if (undo[12 - (iter*12)] == 'W') {
					board[from->locY][from->locX] = pieces[3];
					} else {
					board[from->locY][from->locX] = pieces[9];
					}
					break;
				case 'Q':
					if (undo[12 - (iter*12)] == 'W') {
					board[from->locY][from->locX] = pieces[4];
					} else {
					board[from->locY][from->locX] = pieces[10];
					}
					break;
				case 'K':
					if (undo[12 - (iter*12)] == 'W') {
					board[from->locY][from->locX] = pieces[5];
					} else {
					board[from->locY][from->locX] = pieces[11];
					}
					break;
				default:
					break;
			}
			*moveCnt = *moveCnt - 2;
		} else {
			printf("ERROR: no piece at %c%d\n", undo[7], undo[8] - 48);
		}
	}
} else {
	printf("\nERROR: CANNOT UNDO: NOT ENOUGH MOVES!\n");
}

}

