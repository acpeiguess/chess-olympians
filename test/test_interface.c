/* Tests the console interface */

#include <stdio.h>
#include <stdlib.h>
#include "../inc/Pieces.h"
#include "../inc/IO.h"
#include "../inc/Board.h"
#include "../inc/Rules.h"

#define SLEN 80

/************************************** Prototypes ***************************************/
/* evaluates cmd with switch statement */
void evalMainChoice(int cmd, int *WhiteAI, int *BlackAI, int *ingame);
/* evaluates ingame with switch statement */
/* mainly handles input coordinates from user */
void evalGameChoice(int ingame, char* move, t_coords* from, t_coords* to);

/************************************ End Prototypes *************************************/

int main(){
  /* initial variables */
  t_piece *board[8][8];
  int cmd = -1;
  int ingame = 0;
  int WhiteAI = 0;
  int BlackAI = 0;
  t_coords from;
  t_coords to;
  char* move;
  
  /* Initialization of variable */
  move = malloc(sizeof(char)*SLEN);
  initBoard(board);
  
  while(cmd != 0){
#ifndef DEBUG
    system("clear");
#endif
    printMainMenu();
    cmd = getInt("Your Choice: ");
    evalMainChoice(cmd, &WhiteAI, &BlackAI, &ingame);
    while(ingame){
      if(WhiteAI){
	/* AI team needs to implement their functions here */
      }
      else{
#ifndef DEBUG
	system("clear");
#endif
	printBoard(board);
	printGameMenu();
	ingame = getInt("Your choice: ");
	evalGameChoice(ingame, move, &from, &to); /* Coordinates are set. Rules functions should go after this line */
	movePiece(board, from, to);
      }
      if(BlackAI && ingame){
	/* AI team needs to implement their functions here */
      }
      else if(ingame){
#ifndef DEBUG
	system("clear");
#endif
	printBoard(board);
	printGameMenu();
	ingame = getInt("Your choice: ");
	evalGameChoice(ingame, move, &from, &to); /* Coordinates are set. Rules functions should go after this line */
	movePiece(board, from, to);
      }
      if(!ingame){
	
	
      }
    }
  }/* end while */
  
  free(move);
  
  return 0;
}


/*********************************functions**********************************/

/* evaluates cmd with switch statement */
void evalMainChoice(int cmd, int *WhiteAI, int *BlackAI, int *ingame){
  
  switch(cmd){
    case 0: /* exit */
      printf("Exiting... \n");
      break;
    case 1: /* play human vs human */
      *WhiteAI = 0;
      *BlackAI = 0;
      *ingame = 1;
      break;
      case 2: /* play human vs computer */
	printf("Under Construction :/ \n"
	       "Press ENTER to continue... \n");
	getchar(); getchar();
      break;
    default: /* default */
      printf("That's not an option!\n"
	      "Press ENTER to continue... \n");
      getchar(); getchar();
      break;
    }/* end switch */
  
}

/* evaluates ingame with switch statement */
/* mainly handles input coordinates from user */
void evalGameChoice(int ingame, char* move, t_coords* from, t_coords* to){
  
  switch(ingame){
    case 0: /* quit current game */
      break;
    case 1: /* make move */
      getMove(move);
      while(decodeMove(move, from, to) == 0){
	/* This means decodeMove was ran once and if it fails, the loop will run
	 * getMove until it gets a valid move string from the user */
	getMove(move);
      };    
#ifdef DEBUG
	  printf("move:       %30s\n"
	         "from->locX: %30d\n"
		 "from->locY: %30d\n"
		 "to->locX:   %30d\n"
		 "to->locY:   %30d\n\n", move, from->locX, from->locY, to->locX, to->locY);
#endif
      break;
    case 2: /* undo move */
      printf("Under Construction :/ \n"
	       "Press ENTER to continue... \n");
	getchar(); getchar();
      break;
    default: /* default */
      printf("That's not an option!\n"
	      "Press ENTER to continue... \n");
      getchar(); getchar();
      break;
    
  }
  
}
