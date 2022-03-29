/*****************************************************************************************
 *Project: Chess Olympians
 *Developer: Team 2 / Milk & Dim Sum
 *Description: A graphical program that allows the user
 *             to play chess against another user or
 *             against the computer
 * Notes: 1/17/2014 - Bruce Liu - Created main.c with 
 *        preliminary IO functions and library inclusions
 * 
 *****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../inc/Pieces.h"
#include "../inc/IO.h"
#include "../inc/Board.h"
#include "../inc/Rules.h"
#include "../inc/AI.h"

#define SLEN 80

/************************************** Prototypes ***************************************/
/* evaluates cmd with switch statement */
void evalMainChoice(int cmd, int *WhiteAI, int *BlackAI, int *ingame);
/* evaluates ingame with switch statement */
/* mainly handles input coordinates from user */
void evalGameChoice(int ingame, char* move, t_coords* from, t_coords* to, t_piece *board[8][8], int team);
/*Adam's most expertly written log and undo functions*/
void GameRecord(FILE* out, t_coords* c1, t_coords* c2, t_piece* GameBoard[8][8]);
void UndoMove(int undo[12], t_piece* board[8][8], t_piece* pieces[12], int* moveCnt);

/************************************ End Prototypes *************************************/

int main(){
  /* initial variables */
  t_piece *board[8][8];
  t_piece* pieces[12];
  int cmd = -1;
  int ingame = 0;
  int WhiteAI = 0;
  int BlackAI = 0;
  t_coords from;
  t_coords to;
  char* move;
  FILE* gameLog;
  int team = 0;
  char *betterChoice;
	int k;
  int undo[24];
  int i;
  importPieces(pieces);
  /* Initialization of variable */
  move = malloc(sizeof(char)*SLEN);
  betterChoice= malloc(sizeof(char)*SLEN);
  initBoard(board, pieces);

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

  
  while(cmd != 0){
#ifndef DEBUG
    system("clear");
#endif
    printMainMenu();
    cmd = getInt("Your Choice: ");
    if (cmd ==3)SetCustomBoard(board);
    evalMainChoice(cmd, &WhiteAI, &BlackAI, &ingame);
    while(ingame){
      if(WhiteAI){
	/* AI team needs to implement their functions here */
      }
      else if (!team) {
#ifndef DEBUG
	system("clear");
#endif
	printBoard(board);
	printf("TURN: WHITE\n\n\n");
	printGameMenu();
	/*ingame = getInt("Your choice: ");*/
	
	scanf("%s", betterChoice);
	for(k=0;k<4;k++)
	{
		betterChoice[k]=toUpper(betterChoice[k]);	
	}
	if ((betterChoice[0]=='Q')&&(betterChoice[1]=='U')&&(betterChoice[2]=='I')&&(betterChoice[3]=='T'))
	{
		ingame = 0;
		cmd = 0;
	}
	else if ((betterChoice[0]=='U')&&(betterChoice[1]=='N')&&(betterChoice[2]=='D')&&(betterChoice[3]=='O'))
	{
		ingame = 2;
	}
	else
	{
		move = betterChoice;
		ingame = 1;
		
	}
	 evalGameChoice(ingame, move, &from, &to, board, team);/* Coordinates are set. Rules functions should go after this line */
	if (ingame == 1)	
	{
		
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
		movePiece(board, from, to);
		(*moveCnt)++;
		team=BLACK;
	}
	if (ingame == 2) {
		UndoMove(undo, board, pieces, moveCnt);
		for (i = 0; i < 24; i++) {
			printf("%c", undo[i]);
		}
		team = WHITE;
	}
      }
	

      if(BlackAI && ingame){
		printf("Press enter to continue: ");
		char c;
		scanf("%c", &c);
		scanf("%c", &c);
		t_move aiMove = findBestMove(board, BLACK, DEPTH);
		
		GameRecord(gameLog, &(aiMove.pieceLoc), &(aiMove.pieceDest), board);
		
		movePiece(board, aiMove.pieceLoc, aiMove.pieceDest);
		/*printf("\n%d%d\n", aiMove.pieceLoc.locX, aiMove.pieceLoc.locY);*/
		
		team=WHITE;
      }
      else if(ingame && team){
#ifndef DEBUG
	system("clear");
#endif
	printBoard(board);
	printf("TURN: BLACK\n\n\n");
	printGameMenu();
	/*ingame = getInt("Your choice: ");*/
	
	scanf("%s", betterChoice);
	for(k=0;k<4;k++)
	{
		betterChoice[k]=toUpper(betterChoice[k]);	
	}
	if ((betterChoice[0]=='Q')&&(betterChoice[1]=='U')&&(betterChoice[2]=='I')&&(betterChoice[3]=='T'))
	{
		cmd = 0;
		ingame = 0;
	}
	else if ((betterChoice[0]=='U')&&(betterChoice[1]=='N')&&(betterChoice[2]=='D')&&(betterChoice[3]=='O'))
	{
		ingame = 2;
	}
	else
	{
		move = betterChoice;
		ingame = 1;
	}

	evalGameChoice(ingame, move, &from, &to, board, team); /* Coordinates are set. Rules functions should go after this line */
	if (ingame == 1)
	{
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
		movePiece(board, from, to);
		(*moveCnt)++;
		team=WHITE;
	}
	if (ingame == 2) {
		UndoMove(undo, board, pieces, moveCnt);

		for (i = 0; i < 24; i++) {
			printf("%c", undo[i]);
		}
		team = BLACK;
	}
      }
      if(!ingame){
	
	
      }
    }
  }/* end while */
  
  free(move);
  free(moveCnt);
  
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
      *WhiteAI = 0;
      *BlackAI = 1;
      *ingame = 1;;
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
void evalGameChoice(int ingame, char* move, t_coords* from, t_coords* to, t_piece *board[8][8], int team){
  
  switch(ingame){
    case 0: /* quit current game */
      break;
    case 1: /* make move */
      /*getMove(move);*/
      while(decodeMove(move, from, to, board, team) == 0){
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
/*function call located in main*/
      break;
    default: /* default */
      printf("That's not an option!\n"
	      "Press ENTER to continue... \n");
      getchar(); getchar();
      break;
    
  }
  
}


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


