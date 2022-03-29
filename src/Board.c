/*
 * Team 2 / Milk N Dim Sum
 * Board.h
 */

/*************************************** Notes **********************************************
 * 1/17/2014 - Bruce Liu - Created module and declared basic functions.
 * 
 * *********************************** End Notes ********************************************/

#include "../inc/Board.h"
#include <stdio.h>
#include <string.h>
#include "../inc/IO.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* initializes board to all NULL */
void initBoard(t_piece *board[8][8], t_piece* pieces[12])
{
	t_piece *bp = malloc(sizeof(t_piece));
	t_piece *bkn = malloc(sizeof(t_piece));
	t_piece *bb = malloc(sizeof(t_piece));
	t_piece *br = malloc(sizeof(t_piece));
	t_piece *bq = malloc(sizeof(t_piece));
	t_piece *bk = malloc(sizeof(t_piece));

	t_piece *wp = malloc(sizeof(t_piece));
	t_piece *wkn = malloc(sizeof(t_piece));
	t_piece *wb = malloc(sizeof(t_piece));
	t_piece *wr = malloc(sizeof(t_piece));
	t_piece *wq = malloc(sizeof(t_piece));
	t_piece *wk = malloc(sizeof(t_piece));

	initPiece(bp, BLACK, PAWN);
	pieces[0] = bp;
	initPiece(bkn, BLACK, KNIGHT);
	pieces[1] = bkn;
	initPiece(bb, BLACK, BISHOP);
	pieces[2] = bb;
	initPiece(br, BLACK, ROOK);
	pieces[3] = br;
	initPiece(bq, BLACK, QUEEN);
	pieces[4] = bq;
	initPiece(bk, BLACK, KING);
	pieces[5] = bk;

	initPiece(wp, WHITE, PAWN);
	pieces[6] = wp;
	initPiece(wkn, WHITE, KNIGHT);
	pieces[7] = wkn;
	initPiece(wb, WHITE, BISHOP);
	pieces[8] = wb;
	initPiece(wr, WHITE, ROOK);
	pieces[9] = wr;
	initPiece(wq, WHITE, QUEEN);
	pieces[10] = wq;
	initPiece(wk, WHITE, KING);
	pieces[11] = wk;

	board[0][0] = board[0][7] = wr;
	board[0][1] = board[0][6] = wkn;
	board[0][2] = board[0][5] = wb;
	board[0][3] = wq;
	board[0][4] = wk;

	board[7][0] = board[7][7] = br;
	board[7][1] = board[7][6] = bkn;
	board[7][2] = board[7][5] = bb;
	board[7][3] = bq;
	board[7][4] = bk;

	int i,j;
	for(i = 0; i < 8; i++)
	{
		board[1][i] = wp;
		board[6][i] = bp;
	}
	
	for(j = 2; j < 6; j++)
		for(i = 0; i < 8; i++)
		{
			board[j][i] = NULL;
		}
}


void copyBoard(t_piece *oldBoard[8][8], t_piece *newBoard[8][8])
{
	int i, j;
	for(j = 0; j < 8; j++)
		for(i = 0; i < 8; i++)
		{
			newBoard[i][j] = oldBoard[i][j];
		}
}


void SetCustomBoard(t_piece *GameBoard[8][8])
{
	/*Initialize all the pointers to each piece*/
	t_piece *bp = (t_piece*)malloc(sizeof(t_piece));
	t_piece *bkn =(t_piece*)malloc(sizeof(t_piece));
	t_piece *bb = (t_piece*)malloc(sizeof(t_piece));
	t_piece *br = (t_piece*)malloc(sizeof(t_piece));
	t_piece *bq = (t_piece*)malloc(sizeof(t_piece));
	t_piece *bk = (t_piece*)malloc(sizeof(t_piece));

	t_piece *wp = (t_piece*)malloc(sizeof(t_piece));
	t_piece *wkn = (t_piece*)malloc(sizeof(t_piece));
	t_piece *wb = (t_piece*)malloc(sizeof(t_piece));
	t_piece *wr = (t_piece*)malloc(sizeof(t_piece));
	t_piece *wq = (t_piece*)malloc(sizeof(t_piece));
	t_piece *wk = (t_piece*)malloc(sizeof(t_piece));

	initPiece(bp, BLACK, PAWN);
	initPiece(bkn, BLACK, KNIGHT);
	initPiece(bb, BLACK, BISHOP);
	initPiece(br, BLACK, ROOK);
	initPiece(bq, BLACK, QUEEN);
	initPiece(bk, BLACK, KING);

	initPiece(wp, WHITE, PAWN);
	initPiece(wkn, WHITE, KNIGHT);
	initPiece(wb, WHITE, BISHOP);
	initPiece(wr, WHITE, ROOK);
	initPiece(wq, WHITE, QUEEN);
	initPiece(wk, WHITE, KING);


	/*char input[10] = { "aaaa" };*/
	char piece[3], loc[3];
	int x, y, bad_entry = 0;

	/*Initialize the board to all NULL values*/
	initBlankBoard(GameBoard);


	while (1)
	{



		/*Prints the gameboard each time a user places a piece so they can keep track*/
		printBoard(GameBoard);

		/*Prints Menu*/
		printf("Place a piece or type Q to exit \n"
			"Use \"b\" for Black and \"w\" for White \n"
			"followed by the first letter of the piece.\n"
			"Please use \"n\" for the Knight.\n"
			"Example: \"bn a4\" would indicate \"Black Knight on A4\"\n\n");

		/*Invaid entry flag. This flag is set if the user inputs incorrect parameters*/
		if (bad_entry == 1)
		{
			printf("ERROR: Invalid coordianate or peice. \n Please Enter a valid coordiante and piece selection \n\n");
			bad_entry = 0;
		}

		/*Piece selection. Input verification for piece selection is at the bottom of the function*/
		printf("Select a peice: ");
		scanf("%s", piece);

		/*Checks for user quit*/
		if ((piece[0] == 'q') || (piece[0] == 'Q'))
			break;

		/*Coordinate input*/
		printf("Enter coordinate: ");
		scanf("%s", loc);
		printf("\n\n");


		/*Maks sure the user doesn't enter a coordinate too large*/
		if ((toUpper(loc[0]) - 65 > 7) || (loc[1] - 49 > 7))
		{
			bad_entry = 1;
			continue;
		}


		


		x = toUpper(loc[0]) - 65;
		y = loc[1] - 49;
		/*
 * 		x equals ascii value of 'A'(65) minus 65 which is '0'
 * 				y equals ascii value of '4'(52) minus 49 which equals '4'
 * 						*/


		/*uses an "If Then" ladder to check the choice*/
		if (strcmp(piece, "bp") == 0)
		{
			GameBoard[y][x] = bp;
		}
		else if (strcmp(piece, "bk") == 0)
		{
			GameBoard[y][x] = bk;
		}
		else if (strcmp(piece, "bb") == 0)
		{
			GameBoard[y][x] = bp;
		}
		else if (strcmp(piece, "br") == 0)
		{
			GameBoard[y][x] = br;
		}
		else if (strcmp(piece, "bq") == 0)
		{
			GameBoard[y][x] = bq;
		}
		else if (strcmp(piece, "bn") == 0)
		{
			GameBoard[y][x] = bkn;
		}
		else if (strcmp(piece, "wp") == 0)
		{
			GameBoard[y][x] = wp;
		}
		else if (strcmp(piece, "wk") == 0)
		{
			GameBoard[y][x] = wk;
		}
		else if (strcmp(piece, "wq") == 0)
		{
			GameBoard[y][x] = wq;
		}
		else if (strcmp(piece, "wr") == 0)
		{
			GameBoard[y][x] = wr;
		}
		else if (strcmp(piece, "wb") == 0)
		{
			GameBoard[y][x] = wb;
		}
		else if (strcmp(piece, "wn") == 0)
		{
			GameBoard[y][x] = wkn;
		}

		/*If no piece was found then the user entered an invalid piece. Invalid entry flag is set. */
		else
			bad_entry = 1;

	}
}


void initBlankBoard(t_piece *board[8][8])
{
	int i, j;

	for (j = 0; j < 8; j++)
	for (i = 0; i < 8; i++)
	{
		board[j][i] = NULL;
	}
}

/*add single piece to board */
void addPiece(t_piece *board[8][8], t_piecetype type, t_player team, t_coords position){
  
  t_piece *piece = (t_piece*)malloc(sizeof(t_piece));
  initPiece(piece, team, type);
  board[position.locY][position.locX] = piece;
  
}








