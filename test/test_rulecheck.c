/*                                          */
/*      CHARLIE DEFINITELY SUCKZZZZ         */
/*           LIKE, SERIOUSLY                */
/* MUST WAIT FOR THE BOARD.H TO FINISH      */
/* SO THAT I CAN RETHINK THIS A BIT         */
/*                                          */
/* made changes to checkloc and checkloc2   */
/*                                          */

#include "../inc/Rules.h"

int i,j;

/* Point System
   KING   = 1000
   QUEEN  = 88
   BISHOP = 33
   KNIGHT = 32
   ROOK   = 51
   PAWN   = 10    */

int checkLoc (t_piece *GameBoard[8][8], t_coords coords, int turn)
{
	/*this function is more complicated than this but for the alpha release this will be it*/
	printf("checking location of piece");
	t_piece *SelectedPiece = GameBoard[coords.locY][coords.locX];
	if (SelectedPiece->team == turn)
		return 1; /*1 is moveable*/
	else 
		return 0; /*0 is not moveable*/
	/*must return 1 or 0  if this grid contain the piece that is movable*/
}
int checkLoc2 (t_coords coords, int legal[8][8])
{	
	printf("checking legal moves");
	if (legal[coords.locY][coords.locX] == 1)
		return 1;
	else 
		return 0;
	/*must return 1 or 0 if the destination is legal to move*/
}

void movePiece(t_piece *GameBoard[8][8], t_coords coords1,t_coords coords2)
{
	/*if (GameBoard[coords1.locY][coords1.locX]->points == PAWN)
	{
		if ((GameBoard[coords1.locY][coords1.locX]->team == WHITE)&&(coords2.locX == coords1.locX)&&(coords2.locY == 7))
		{
			//ask player later for now make it queen by default
			GameBoard[coords2.locY][coords2.locX] = malloc(sizeof(t_piece))
			GameBoard[coords2.locY][coords2.locX]->points = QUEEN;
			GameBoard[coords2.locY][coords2.locX]->team = WHITE;
			//add the pointer to the list of all pointers  so that it may be freed after the game is done
		}
		if ((GameBoard[coords1.locY][coords1.locX]->team == BLACK)&&(coords2.locX == coords1.locX)&&(coords2.locY == 0))
		{
			//ask player later for now make it queen by default
			GameBoard[coords2.locY][coords2.locX] = malloc(sizeof(t_piece))
			GameBoard[coords2.locY][coords2.locX]->points = QUEEN;
			GameBoard[coords2.locY][coords2.locX]->team = BLACK;
			//add the pointer to the list of all pointers  so that it may be freed after the game is done
		}
	}*/
	GameBoard[coords2.locY][coords2.locX]= GameBoard[coords1.locY][coords1.locX];
	GameBoard[coords1.locY][coords1.locX]= NULL;
}
#ifdef ALPHA
void genLegal(t_coords coords, t_piece *GameBoard[8][8], int legal[8][8])
{
	printf("generating legal bit array for pieces");
	int locY=coords.locY;
	int locX=coords.locX;
	t_piece *cpiece = GameBoard[locY][locX];
	int i ,j;
	for (i=0;i<8;i++) /*just in case this will clear the entire legal array*/
		for(j=0;j<8;j++)
		{
			legal [j][i]=0;
		}
int cteam =cpiece->team;
int choice = cpiece->points;

switch (choice){
	/*pawn needs to do EN PASSANT*/
	case PAWN:
		printf("bit array to be created for pawn"); 
		if (locY==1 && cteam==WHITE)/*White team pawn special first move*/
			{
				if (GameBoard[locY+1][locX] == NULL)
					{
						legal [locY+1][locX]=1;
						if (GameBoard[locY+2][locX] == NULL)
						{
							legal [locY+2][locX]=1;
						}
					}
				else 
					{
						legal [locY+1][locX] =0;
						legal [locY+2][locX] =0;
					}
			}
			else if (locY==6 && cteam==BLACK) /*Black team pawn special first move*/
			{
				if (GameBoard[locY-1][locX] == NULL)
					{
						legal [locY-1][locX]=1;
						if (GameBoard[locY+2][locX] == NULL)
						{
							legal [locY-2][locX]=1;
						}
					}
				else 
					{
						legal [locY-1][locX] =0;
						legal [locY-2][locX] =0;
					}
			}
			if (cteam==WHITE)/*white team move forward*/
			{
				if (GameBoard[locY+1][locX]==NULL)
				{
					legal[locY+1][locX]=1;
				}
				if ((!GameBoard[locY+1][locX+1]==NULL)&&(GameBoard[locY+1][locX+1]->team!=cteam)) /*kill move to the right*/
				{
					if ((locX+1)<7)
					legal[locY+1][locX+1]=1;
				}
				if ((!GameBoard[locY+1][locX-1]==NULL)&&(GameBoard[locY+1][locX-1]->team!=cteam)) /*kill move to the left*/
				{
					if ((locX-1)>0)
					legal[locY+1][locX-1]=1;
				}
			}
			if (cteam==BLACK)/*black team move forward*/
			{
				if (GameBoard[locY-1][locX]==NULL)
				{
					legal[locY-1][locX]=1;
				}
				if ((!GameBoard[locY-1][locX+1]==NULL)&&(GameBoard[locY-1][locX+1]->team!=cteam)) /*kill move to the right*/
				{
					if ((locX+1)<7)
					legal[locY-1][locX+1]=1;
				}
				if ((!GameBoard[locY-1][locX-1]==NULL)&&(GameBoard[locY-1][locX-1]->team!=cteam)) /*kill move to the left*/
				{
					if ((locX-1)>0)
					legal[locY-1][locX-1]=1;
				}
			}
			break;
	 

	case ROOK: /*white rook moves forward (kevin)*/
		printf("bit array to be created for rook");
 		if(cteam == WHITE) /* white team's turn*/
                        {
                                for(i=locY;i<(8-locY);i++){

                                        /*checking column in front of rook*/
                                        if(GameBoard[locY+i][locX] == NULL){
                                                legal[locY+i][locX] = 1;
                                        } /* fi */
                                        if(!GameBoard[locY+i][locX]==NULL)&&(GameBoard[locY+i][locX]->team!=cteam)){
                                                        legal[locY+i][locX] = 1;
							break;
                                        }/*fi*/
                                }/*rof*/

                                for(i=0;i<locY;i++){
                                        /*checking column behind rook*/
                                        if(GameBoard[locY-i][locX] == NULL){
                                                legal[locY-i][locX] = 1;
                                        }/*fi*/
                                        if(!GameBoard[locY-i][locX]==NULL)&&(GameBoard[locY-i][locX]->team!=cteam)){
                                                        legal[locY-i][locX] = 1;
							break;
                                        }/*fi*/
                                }/*rof*/

                                for(i=locX;i<(8-locX);i++){
                                        /*checking row to the right of rook*/
                                        if(GameBoard[locY][locX+i] == NULL){
                                                legal[locY][locX+i] = 1;
                                        }/*fi*/
                                        if(!GameBoard[locY][locX+i]==NULL)&&(GameBoard[locY][locX+i]->team!=cteam)){
                                                        legal[locY][locX+i] = 1;
							break;
                                        }/*fi*/
                                }/*rof*/

                                for(i=locX;i<locX;i++){
                                        /*checking row to the left of rook*/
                                        if(GameBoard[locY][locX-i] == NULL){
                                                legal[locY][locX-i] = 1;
					}/*fi*/
                                        if(!GameBoard[locY][locX-i]==NULL)&&(GameBoard[locY][locX-i]->team!=cteam)){
                                                        legal[locY][locX-i] = 1;
							break;
                                        }/*fi*/
                                }/*rof*/

                        } /*fi*/

                        if(cteam == BLACK) /* black team's turn*/
                        {
                                for(i=locY;i<(8-locY);i++){

                                        /*checking column in front of rook*/
                                        if(GameBoard[locY+i][locX] == NULL){
                                                legal[locY+i][locX] = 1;
                                        } /* fi */
                                        if(!GameBoard[locY+i][locX]==NULL)&&(GameBoard[locY+i][locX]->team!=cteam)){
                                                        legal[locY+i][locX] = 1;
							break;
                                        }/*fi*/
                                }/*rof*/

                                for(i=0;i<locY;i++){
                                        /*checking column behind rook*/
                                        if(GameBoard[locY-i][locX] == NULL){
                                                legal[locY-i][locX] = 1;
                                        }/*fi*/
                                        if(!GameBoard[locY-i][locX]==NULL)&&(GameBoard[locY-i][locX]->team!=cteam)){
                                                        legal[locY-i][locX] = 1;
							break;
                                        }/*fi*/
                                }/*rof*/

                                for(i=locX;i<(8-locX);i++){
                                        /*checking row to the right of rook*/
                                        if(GameBoard[locY][locX+i] == NULL){
                                                legal[locY][locX+i] = 1;
                                        }/*fi*/
                                        if(!GameBoard[locY][locX+i]==NULL)&&(GameBoard[locY][locX+i]->team!=cteam)){
							legal[locY][locX+i] = 1;
							break;
                                        }/*fi*/
                                }/*rof*/

                                for(i=locX;i<locX;i++){
                                        /*checking row to the left of rook*/
                                        if(GameBoard[locY][locX-i] == NULL){
                                                legal[locY][locX-i] = 1;
                                        }/*fi*/
                                        if(!GameBoard[locY][locX-i]==NULL)&&(GameBoard[locY][locX-i]->team!=cteam)){
                                                        legal[locY][locX-i] = 1;
							break;
                                        }/*fi*/
                                }/*rof*/

                        } /*fi*/
                        /*end of rook case*/

                        break;

                case BISHOP: /*bishop (kevin) */
			printf("bit array to be created for bishop");
                        if(cteam == WHITE)/*white team's turn*/
                        {
                                for(i=0;i<(8-locY);i++){  /* this loop needs to be adjusted for the boundary */
                                        
                                                /* checking upper right diagonal */
                                                if(GameBoard[locY+i][locX+i] == NULL){
                                                        legal[locY+i][locX+i] = 1;
                                                }
                                                if(!GameBoard[locY+i][locX+i]==NULL)&&(GameBoard[locY+i][locX+i]->team!=cteam)){
                                                        legal[locY+i][locX+i] = 1;
							break; 
                                                }
                                        
                                }/*rof*/

                                for(i=0;i<(8-locY);i++){
                                        
                                                /*checking upper left diagonal */

						if(GameBoard[locY+i][locX-i] == NULL){
                                                        legal[locY+i][locX-i] = 1;
                                                }
                                                if(!GameBoard[locY+i][locX-i]==NULL)&&(GameBoard[locY+i][locX-i]->team!=cteam)){
                                                        legal[locY+i][locX-i] = 1;
							break;
                                                }
                                        
                                )/*rof*/


                                for(i=0;i<locY;i++){
                                        
                                                /*checking lower right diagonal*/
                                                if(GameBoard[locY-i][locX+i] == NULL){
                                                        legal[locY-i][locX+i] = 1;
                                                }
                                                if(!GameBoard[locY-i][locX+i]==NULL)&&(GameBoard[locY-i][locX+i]->team!=cteam)){
                                                        legal[locY-i][locX+i] = 1;
							break;
                                                }
                                        
                                }


                                for(i=0;i<locY;i++){
                                        
                                                /*checking lower left diagonal*/
                                                if(GameBoard[locY-i][locX-i] == NULL){
                                                        legal[locY-i][locX-i] = 1;
                                                }
                                                if(!GameBoard[locY-i][locX-i]==NULL)&&(GameBoard[locY-i][locX-i]->team!=cteam)){
                                                        legal[locY-i][locX-i] = 1;
							break;
                                                }
                                        
                                }

                        }
						
						
			if(cteam == BLACK) /*black team's turn*/
                        {
                                for(i=0;i<(8-locY);i++){  /* this loop needs to be adjusted for the boundary */
                                        
                                                /* checking upper right diagonal */
                                                if(GameBoard[locY+i][locX+i] == NULL){
                                                        legal[locY+i][locX+i] = 1;
                                                }
                                                if(!GameBoard[locY+i][locX+i]==NULL)&&(GameBoard[locY+i][locX+i]->team!=cteam)){
                                                        legal[locY+i][locX+i] = 1;
							break; 
                                                }
                                        
                                }/*rof*/

                                for(i=0;i<(8-locY);i++){
                                        
                                                /*checking upper left diagonal */

						if(GameBoard[locY+i][locX-i] == NULL){
                                                        legal[locY+i][locX-i] = 1;
                                                }
                                                if(!GameBoard[locY+i][locX-i]==NULL)&&(GameBoard[locY+i][locX-i]->team!=cteam)){
                                                        legal[locY+i][locX-i] = 1;
							break;
                                                }
                                        
                                )/*rof*/


                                for(i=0;i<locY;i++){
                                        
                                                /*checking lower right diagonal*/
                                                if(GameBoard[locY-i][locX+i] == NULL){
                                                        legal[locY-i][locX+i] = 1;
                                                }
                                                if(!GameBoard[locY-i][locX+i]==NULL)&&(GameBoard[locY-i][locX+i]->team!=cteam)){
                                                        legal[locY-i][locX+i] = 1;
							break;
                                                }
                                        
                                }


                                for(i=0;i<locY;i++){
                                        
                                                /*checking lower left diagonal*/
                                                if(GameBoard[locY-i][locX-i] == NULL){
                                                        legal[locY-i][locX-i] = 1;
                                                }
                                                if(!GameBoard[locY-i][locX-i]==NULL)&&(GameBoard[locY-i][locX-i]->team!=cteam)){
                                                        legal[locY-i][locX-i] = 1;
							break;
                                                }
                                        
                                }

                        }
                        /* end of bishop case*/
                        break;


	case KNIGHT: /* Knight */
		printf("bit array to be created for knight");
		/* 1 tile up, 2 tiles left */
		if ((locY <= 6) && (locX >= 2) && ((GameBoard[locY+1][locX-2] == NULL) || GameBoard[locY+1][locX-2]->team != cteam))
		{
			legal[locY+1][locX-2] = 1;
		}
		/* 2 tiles up, 1 tile left */
		if ((locY <= 5) && (locX >= 1) && ((GameBoard[locY+2][locX-1] == NULL) || GameBoard[locY+2][locX-1]->team != cteam))
		{
			legal[locY+2][locX-1] = 1;
		}
		/* 2 tiles up, 1 tile right */
		if ((locY <= 5) && (locX >= 6) && ((GameBoard[locY+2][locX+1] == NULL) || GameBoard[locY+2][locX+1]->team != cteam))
		{
			legal[locY+2][locX+1] = 1;
		}
		/* 1 tile up, 2 tiles right */
		if ((locY <= 6) && (locX <= 5) && ((GameBoard[locY+1][locX+2] == NULL) || GameBoard[locY+1][locX+2]->team != cteam))
		{
			legal[locY+1][locX+2] = 1;
		}
		/* 1 tile down, 2 tiles right */
		if ((locY >= 1) && (locX <= 5) && ((GameBoard[locY-1][locX+2] == NULL) || GameBoard[locY-1][locX+2]->team != cteam))
		{
			legal[locY-1][locX+2] = 1;
		}
		/* 2 tiles down, 1 tile right */
		if ((locY >= 2) && (locX >= 6) && ((GameBoard[locY-2][locX+1] == NULL) || GameBoard[locY-2][locX+1]->team != cteam))
		{
			legal[locY-2][locX+1] = 1;
		}
		/* 2 tiles down, 1 tile left */
		if ((locY >= 2) && (locX >= 1) && ((GameBoard[locY-2][locX-1] == NULL) || GameBoard[locY-2][locX-1]->team != cteam))
		{
			legal[locY-2][locX-1] = 1;
		}
		/* 1 tile down, 2 tiles left */
		if ((locY >= 1) && (locX >= 2) && (GameBoard[locY-1][locX-2] == NULL))
		{
			legal[locY-1][locX-2] = 1;
		}
		break;
			
	case KING: printf("bit array for king to be created");
	/*if (cteam==0) {*/ /*King of White*/
			for (i = -1; i < 2; i++) {
				for (j= -1; j < 2; j++) {
					if (j!=0 && i!=0 && (locY + i > 0) && (locY + i < 7) && (locX + j > 0) && (locX + j < 7) {
						if (GameBoard[locY + i][locX + j]->team != GameBoard[locY][locX]->team) {
							GameBoard[locY + i][locX + j]=1;
						}
					}
				}
			}
		/*}
		if (cteam==1) { King of Black
			for (i = -1; i < 2; i++) {
				for (j= -1; j < 2; j++) {
					if (j!=0 && i!=0 && (LocY + i > 0) && (LocY + i < 7) && (LocX + j > 0) && (LocX + j < 7)  {
						if (GameBoard[LocY + i][LocX + j]==NULL) {
							GameBoard[LocY + i][LocX + j]=1;
						}
					}
				}
			}
		}*/
		break;

	}
}
#endif
