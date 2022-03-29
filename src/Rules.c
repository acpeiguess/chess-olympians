/*                                          */
/*      CHARLIE DEFINITELY SUCKZZZZ         */
/*           LIKE, SERIOUSLY                */
/* MUST WAIT FOR THE BOARD.H TO FINISH      */
/* SO THAT I CAN RETHINK THIS A BIT         */
/*                                          */
/* 					    */


#include "../inc/Rules.h"


#define LEGALTEST


int i,j;

static int charlie_legal[8][8];/*for charlie by charlie; don't touch*/
static int kArray[8][8];/*0 for nothing, 1 for path, 2 for piece checking the king, 3 for pinned piece, 9 for the king's location*/
static t_piece *pieces[12];
void importPieces(t_piece *PIECES[12])
{
	for(j=0;j<12;j++)
		pieces[j]=PIECES[j];
}

#ifdef LEGALTEST
void printlegal(int testlegal[8][8])
{
	int x,y;
	for(y=7;y>=0;y--)
	{
		printf(" +---+---+---+---+---+---+---+---+\n");
		printf("%d",y+1);
		for(x=0;x<8;x++)
		{
			
			printf("| %d ",testlegal[y][x]);
		}
		printf("|\n");
	}
	printf(" +---+---+---+---+---+---+---+---+\n");
	printf("   A   B   C   D   E   F   G   H  \n");
	printf("\n\n");
}
#endif

/* Point System
   KING   = 10000
   QUEEN  = 88
   BISHOP = 33
   KNIGHT = 32
   ROOK   = 51
   PAWN   = 10    */



int checkLoc (t_piece *GameBoard[8][8], int locY, int locX, int turn)
{
	int v,u;
	int isChecked=0;
	int checkmate=0;
	int protect = 0;
	/*int stalemate = 0;*/


	/*scan the game board for king of that turn*/
	for (u=0;u<8;u++)
	{	
		for (v=0;v<8;v++)
		{
			if ((GameBoard[u][v]!=NULL)&&(GameBoard[u][v]->points == KING)&&(GameBoard[u][v]->team==turn))
			{ 
				t_coords loc;
				loc.locY = u;
				loc.locX = v;
				isChecked = Check(GameBoard, loc, turn);
				
				if (isChecked){
					
					checkmate = Checkmate(kArray,GameBoard,turn,charlie_legal);
					if (checkmate)
					{
						printf("CHECKMATE\n\n");
					}
				}
				else
				{
					/*stalemate = Stalemate(GameBoard,loc);
					if (stalemate)
					{
						printf("STALEMATE\n\n");
						return 0;
					}*/
				}
				break;
			}
	}	}
		
	
	/*this function is more complicated than this but for the alpha release this will be it*/
	if (GameBoard[locY][locX] == NULL)
	{
		printf("There is no piece here \n");
		return 0;
	}
	else
	{
		t_piece *SelectedPiece = GameBoard[locY][locX];
		if (!(SelectedPiece->team == turn))
		{
			if(turn)
			{
				printf("Wrong Team; Currently it is %s Turn\n","BLACK");				
			}
			else
			{
				printf("Wrong Team; Currently it is %s Turn\n","WHITE");
			}
			return 0; /*0 is not moveable*/
		}
		if (kArray[locY][locX]==3)
		{
			printf("This piece is pinned to the king");
			return 0;
		}
		
		if (SelectedPiece->team == turn)
		{	
			t_coords coordinates;
			coordinates.locX = locX;
			coordinates.locY = locY;
			genLegal(coordinates, GameBoard, charlie_legal);
			#ifdef LEGALTEST
			printlegal(charlie_legal);
			#endif
			/*if the king is in check the only pieces that is legal to move are the pieces that can protect/kill the king and the king itself*/
			/*look through legal and see if it can kill or protect*/
			for (j=0;j<8;j++)
				for (i=0;i<8;i++)
				{
					if ((charlie_legal[j][i] == 1)&&((kArray[j][i]==1)||(kArray[j][i]==2)))
					protect =1;
				}
			if ((isChecked)&&(!protect))
			{
				return 0;
			}
			else
				return 1; /*1 is moveable*/
		}
		
	}
return 0;
	/*must return 1 or 0  if this grid contain the piece that is movable*/
}

int checkLoc2 (t_coords *coords)
{	
	if (charlie_legal[coords->locY][coords->locX] == 1)
	{	
		return 1;
	}
	else 
	{
		printf("Not a Legal Move");
		return 0;
	}
	/*must return 1 or 0 if the destination is legal to move*/
}

int movePiece(t_piece *GameBoard[8][8], t_coords coords1,t_coords coords2)
{	
	/*if (GameBoard[coords1.locY][coords1.locX]->points == PAWN)
	{
		if ((GameBoard[coords1.locY][coords1.locX]->team == WHITE)&&(coords2.locY == 7))
		{
			int promo=0;
			printf(	"Pawn is being promoted Please choose the piece type\n"
				"1. Queen\n"
				"2. Rook\n"
				"3. Bishop\n"
				"4. Knight\n"
				"Please enter your choice number: ");
			scanf("%d",&promo);
			switch (promo){
			case 1:GameBoard[coords1.locY][coords1.locX] = pieces[10];break;
			case 2:GameBoard[coords1.locY][coords1.locX] = pieces[9];break;
			case 3:GameBoard[coords1.locY][coords1.locX] = pieces[8];break;
			case 4:GameBoard[coords1.locY][coords1.locX] = pieces[7];break;
			default:GameBoard[coords1.locY][coords1.locX] = pieces[10];break;}
		}
		if ((GameBoard[coords1.locY][coords1.locX]->team == BLACK)&&(coords2.locY == 0))
		{	int promo=0;
			printf(	"Pawn is being promoted Please choose the piece type\n"
				"1. Queen\n"
				"2. Rook\n"
				"3. Bishop\n"
				"4. Knight\n"
				"Please enter your choice number: ");
			scanf("%d",&promo);
			switch (promo){
			case 1:GameBoard[coords1.locY][coords1.locX] = pieces[4];break;
			case 2:GameBoard[coords1.locY][coords1.locX] = pieces[3];break;
			case 3:GameBoard[coords1.locY][coords1.locX] = pieces[2];break;
			case 4:GameBoard[coords1.locY][coords1.locX] = pieces[1];break;
			default:GameBoard[coords1.locY][coords1.locX] = pieces[10];break;}
		}
	}*/
	int takenPieceValue = 0;
	if(GameBoard[coords2.locY][coords2.locX])
		takenPieceValue = GameBoard[coords2.locY][coords2.locX]->points;
	GameBoard[coords2.locY][coords2.locX]= GameBoard[coords1.locY][coords1.locX];
	GameBoard[coords1.locY][coords1.locX]= NULL;
	/*check for CHECK,CHECKMATE*/
	for (i=0;i<8;i++)
	{	for(j=0;j<8;j++)
		{
			if ((GameBoard[j][i]!=NULL)&&(GameBoard[j][i]->points==KING))
			{	t_coords king; king.locY=j; king.locX=i;
				if ((GameBoard[coords2.locY][coords2.locX]->team==WHITE)&&(GameBoard[j][i]->team==BLACK))
				{
					if (Check(GameBoard, king, BLACK)){printf("CHECK \n\n");}
					
				}
				if ((GameBoard[coords2.locY][coords2.locX]->team==BLACK)&&(GameBoard[j][i]->team==WHITE))
				{
					if (Check(GameBoard, king, WHITE)){printf("CHECK \n\n");}
				}
			}
		}
	}
	return takenPieceValue;
}
/*#ifdef FINAL*/
void genLegal(t_coords coords, t_piece *GameBoard[8][8], int legal[8][8])
{
	int locY=coords.locY;
	int locX=coords.locX;
	t_piece *cpiece = GameBoard[locY][locX];
	int i ,j;
	for (i=0;i<8;i++) /*just in case this will clear the entire legal array*/
		for(j=0;j<8;j++)
		{
			legal [j][i]=0;
		}
	int cteam = cpiece->team;
	int choice = cpiece->points;

switch (choice){
	
	case PAWN:
		pawn(locY,locX,GameBoard,cteam,legal);
		break;
		
	case ROOK:
		rook(locY,locX,GameBoard,cteam,legal);
		break;
		
	case BISHOP:
		bishop(locY, locX,GameBoard,cteam,legal);
		break;
		
	case KNIGHT:
		knight(locY, locX,GameBoard,cteam,legal);
		break;
		
	case QUEEN:
		queen(locY, locX,GameBoard,cteam,legal);
		break;
		
	case KING:
		king( locY, locX,GameBoard,cteam,legal);
		break;
		
}
	
} /*end of genLegal*/

void pawn(int locY, int locX, t_piece *GameBoard[8][8],int cteam,int legal[8][8]){

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
				if (GameBoard[locY-2][locX] == NULL)
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
		if (locY < 7)
			if (GameBoard[locY+1][locX]==NULL)
			{
				legal[locY+1][locX]=1;
			}
		if (locY < 7 && locX < 7)
			if (!(GameBoard[locY+1][locX+1]==NULL)&&(GameBoard[locY+1][locX+1]->team!=cteam)) /*kill move to the right*/
			{
				if ((locX+1)<=7)
				legal[locY+1][locX+1]=1;
			}
		if (locY < 7 && locX > 0)
			if (!(GameBoard[locY+1][locX-1]==NULL)&&(GameBoard[locY+1][locX-1]->team!=cteam)) /*kill move to the left*/
			{
				if ((locX-1)>=0)
				legal[locY+1][locX-1]=1;
			}
	}
	if (cteam==BLACK)/*black team move forward*/
	{
		if (locY > 0)
			if (GameBoard[locY-1][locX]==NULL)
			{
				legal[locY-1][locX]=1;
			}
		if (locY > 0 && locX < 7)
			if (!(GameBoard[locY-1][locX+1]==NULL)&&(GameBoard[locY-1][locX+1]->team!=cteam)) /*kill move to the right*/
			{
				if ((locX+1)<=7)
				legal[locY-1][locX+1]=1;
			}
		if (locY > 0 && locX > 0)
			if (!(GameBoard[locY-1][locX-1]==NULL)&&(GameBoard[locY-1][locX-1]->team!=cteam)) /*kill move to the left*/
			{
				if ((locX-1)>=0)
				legal[locY-1][locX-1]=1;
			}
	}
	

}


void rook(int locY, int locX, t_piece *GameBoard[8][8],int cteam,int legal[8][8])
{
	/*looking foward from the white side looking backward from the black side*/
	for (i=locY+1;i<8;i++)
	{
		if(GameBoard[i][locX] == NULL)
		{
			legal[i][locX] = 1;	
		} /* fi */
		else if(!(GameBoard[i][locX]==NULL)&&(GameBoard[i][locX]->team!=cteam))
		{
			legal[i][locX] = 1;
			break;
		}/*fi*/
		if (!(GameBoard[i][locX]==NULL)&&(GameBoard[i][locX]->team==cteam))
		{
			break;
		}
	}/*rof*/

	/*looking forward from black side looking backward from the white side*/
	for (i=locY-1;i>=0;i--)
	{
		if(GameBoard[i][locX] == NULL)
		{
			legal[i][locX] = 1;
		} /* fi */
		if(!(GameBoard[i][locX]==NULL)&&(GameBoard[i][locX]->team!=cteam))
		{
			legal[i][locX] = 1;
			break;		
		}/*fi*/
		if(!(GameBoard[i][locX]==NULL)&&(GameBoard[i][locX]->team==cteam))
		{
			break;
		}
	}/*rof*/
					
	/*looking right from the white side looking left from the black side*/
	for(i=locX+1;i<8;i++)
	{
		
		if(GameBoard[locY][i] == NULL)
		{
			legal[locY][i] = 1;
		}/*fi*/
		else if(!(GameBoard[locY][i]==NULL)&&(GameBoard[locY][i]->team!=cteam))
		{
			legal[locY][i] = 1;
			break;
		}/*fi*/
		if(!(GameBoard[locY][i]==NULL)&&(GameBoard[locY][i]->team==cteam))
		{
			break;
		}
	}/*rof*/
	/*looking right from the black side looking left from the white side*/
	for(i=locX-1;i>=0;i--)
	{
		if(GameBoard[locY][i] == NULL)
		{
			legal[locY][i] = 1;
		}/*fi*/
		else if(!(GameBoard[locY][i]==NULL)&&(GameBoard[locY][i]->team!=cteam))
		{
			legal[locY][i] = 1;
			break;
		}/*fi*/
		if(!(GameBoard[locY][i]==NULL)&&(GameBoard[locY][i]->team==cteam))
		{
			break;
		}
	}/*rof*/
}

void bishop(int locY, int locX, t_piece *GameBoard[8][8],int cteam,int legal[8][8])
{
	for(i=1;i<8;i++)
	{	/* checking upper right diagonal from white perspective*/
		if((GameBoard[locY+i][locX+i] == NULL)&&(locY+i<8)&&(locX+i<8))
		{
			legal[locY+i][locX+i] = 1;
		}
		if(!(GameBoard[locY+i][locX+i]==NULL)&&(locY+i<8)&&(locX+i<8)&&(GameBoard[locY+i][locX+i]->team!=cteam))
		{
			legal[locY+i][locX+i] = 1;
			break;
		}
		if(!(GameBoard[locY+i][locX+i]==NULL)&&(locY+i<8)&&(locX+i<8)&&(GameBoard[locY+i][locX+i]->team==cteam))
		break;
	}
	for(i=1;i<8;i++)
	{
		/* checking lower left diagonal from white perspective*/
		if((GameBoard[locY-i][locX-i] == NULL)&&(locY-i>=0)&&(locX-i>=0))
		{
			legal[locY-i][locX-i] = 1;
		}
		if(!(GameBoard[locY-i][locX-i]==NULL)&&(locY-i>=0)&&(locX-i>=0)&&(GameBoard[locY-i][locX-i]->team!=cteam))
		{
			legal[locY-i][locX-i] = 1;
			break;
		}
		if(!(GameBoard[locY-i][locX-i]==NULL)&&(locY-i>=0)&&(locX-i>=0)&&(GameBoard[locY-i][locX-i]->team==cteam))
		break;
	}
	for(i=1;i<8;i++)
	{
		/* checking upper left diagonal from white perspective*/
		if((GameBoard[locY+i][locX-i] == NULL)&&(locY+i<8)&&(locX-i>=0))
		{
			legal[locY+i][locX-i] = 1;
		}
		if(!(GameBoard[locY+i][locX-i]==NULL)&&(locY+i<8)&&(locX-i>=0)&&(GameBoard[locY+i][locX-i]->team!=cteam))
		{
			legal[locY+i][locX-i] = 1;
			break;
		}
		if(!(GameBoard[locY+i][locX-i]==NULL)&&(locY+i<8)&&(locX-i>=0)&&(GameBoard[locY+i][locX-i]->team==cteam))
		break;
	}
	for(i=1;i<8;i++)
	{
		/* checking lower right diagonal from white perspective*/
		if((GameBoard[locY-i][locX+i] == NULL)&&(locY-i>=0)&&(locX+i<8))
		{
			legal[locY-i][locX+i] = 1;
		}
		if(!(GameBoard[locY-i][locX+i]==NULL)&&(locY-i>=0)&&(locX+i<8)&&(GameBoard[locY-i][locX+i]->team!=cteam))
		{
			legal[locY-i][locX+i] = 1;
			break;
		}
		if(!(GameBoard[locY-i][locX+i]==NULL)&&(locY-i>=0)&&(locX+i<8)&&(GameBoard[locY-i][locX+i]->team==cteam))
		break;
	}/*rof*/
	/* end of bishop case*/
}

void knight(int locY, int locX, t_piece *GameBoard[8][8],int cteam,int legal[8][8])
{
	/* Knight */
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
	if ((locY <= 5) && (locX <= 6) && ((GameBoard[locY+2][locX+1] == NULL) || GameBoard[locY+2][locX+1]->team != cteam))
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
	if ((locY >= 2) && (locX <= 6) && ((GameBoard[locY-2][locX+1] == NULL) || GameBoard[locY-2][locX+1]->team != cteam))
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
} /* end of knight function */

void queen(int locY, int locX, t_piece *GameBoard[8][8],int cteam,int legal[8][8]){
/*Queen*/
		bishop(locY, locX, GameBoard, cteam, legal);
		rook(locY, locX, GameBoard, cteam, legal);
}



void king(int locY, int locX, t_piece *GameBoard[8][8],int cteam,int legal[8][8])
{
	for (i = -1; i < 2; i++) 
	{
		for (j = -1; j < 2; j++) 
		{
			if (!(j==0 && i==0) && (locY + i >= 0) && (locY + i <= 7) && (locX + j >= 0) && (locX + j <= 7)) 
			{
				if (!(GameBoard[locY + i][locX + j]))
				{
					legal[locY + i][locX + j] = 1;
				} 
				else if (GameBoard[locY + i][locX + j]->team != GameBoard[locY][locX]->team) 
				{
					legal[locY + i][locX + j] = 1;
				}
			}
		}
	}
	t_coords kingloc;
	kingloc.locY = locY;
	kingloc.locX = locX;
	if (!Check(GameBoard, kingloc, cteam)) {
		if (cteam && locY == 7) {
			if (GameBoard[7][0])
				if (!GameBoard[7][1] && !GameBoard[7][2] && !GameBoard[7][3] && (GameBoard[7][0]->team == cteam && GameBoard[7][0]->points == ROOK)) {
					legal[7][2] = 1;
				}
			if (GameBoard[7][7])
				if (!GameBoard[7][5] && !GameBoard[7][6] && (GameBoard[7][7]->team == cteam && GameBoard[7][7]->points == ROOK)) {
					legal[7][6] = 1;
				}
		}
		if (!cteam && locY == 0) {
			if (GameBoard[0][0])
				if (!GameBoard[0][1] && !GameBoard[0][2] && !GameBoard[0][3] && (GameBoard[0][0]->team == cteam && GameBoard[0][0]->points == ROOK)) {
					legal[0][2] = 1;
				}
			if (GameBoard[0][7])
				if (!GameBoard[0][5] && !GameBoard[0][6] && (GameBoard[0][7]->team == cteam && GameBoard[0][7]->points == ROOK)) {
					legal[0][6] = 1;
				}
		}
	}

	/*call suicide function to nullify some movements that will get the king in danger*/
	kingSuicide(GameBoard, legal, kingloc);
}


void superKing(t_piece *GameBoard[8][8],t_coords coords, int cteam, int kingarray[8][8]){

	int locY=coords.locY;
	int locX=coords.locX;
	int i ,j;
	for (i=0;i<8;i++){ /*just in case this will clear the entire legal array*/
		for(j=0;j<8;j++)
		{
				kingarray[j][i]=0;
		}
	}
	
	for(i=locY+1;i<8;i++){

        	/*checking column in front of king*/
        	if(GameBoard[i][locX] == NULL){
			kingarray[i][locX] = 1;
        	} /* fi */
        
		if(!(GameBoard[i][locX]==NULL)){
			if(GameBoard[i][locX]->team == cteam){
					kingarray[i][locX] = 1;
					continue;		
			}/*fi*/
				
			if(GameBoard[i][locX]->team != cteam){
					kingarray[i][locX] = 1;
					break;
			}/*fi*/
			
		}/*fi*/
	}/*rof*/

	for(i=locY-1;i>=0;i--){
	
			/*checking column behind king*/
			if(GameBoard[i][locX] == NULL){
					kingarray[i][locX] = 1;
			}/*fi*/
			if(!(GameBoard[i][locX]==NULL)){
				if(GameBoard[i][locX]->team==cteam){
					kingarray[i][locX] = 1;
					continue;
				}
				if(GameBoard[i][locX]->team!=cteam){
					kingarray[i][locX] = 1;
					break;
				}
			}/*fi*/
	}/*rof*/

	for(i=locX+1;i<8;i++){
			/*checking row to the right of king*/
			if(GameBoard[locY][i] == NULL){
					kingarray[locY][i] = 1;
			}/*fi*/
			if(!(GameBoard[locY][i]==NULL)){
				if(GameBoard[locY][i]->team==cteam){
					kingarray[locY][i] = 1;
					continue;
				}
				if(GameBoard[locY][i]->team!=cteam){
					kingarray[locY][i] = 1;
					break;
				}				
			}/*fi*/
	}/*rof*/

	for(i=locX-1;i>=0;i--){
			/*checking row to the left of king*/
			if(GameBoard[locY][i] == NULL){
					kingarray[locY][i] = 1;
			}/*fi*/
			if(!(GameBoard[locY][i]==NULL)){
				if(GameBoard[locY][i]->team==cteam){
					kingarray[locY][i] = 1;
					continue;
				}
				if(GameBoard[locY][i]->team!=cteam){
					kingarray[locY][i] = 1;
					break;
				}							
			}/*fi*/
	}/*rof*/


	for(i=1;i<8;i++){ 

		/* checking upper right diagonal */
		if((GameBoard[locY+i][locX+i] == NULL)&&(locY+i<8)&&(locX+i<8)) {
				kingarray[locY+i][locX+i] = 1;
		}

		if((!(GameBoard[locY+i][locX+i]==NULL))&&(locY+i<8)&&(locX+i<8)){
			if(GameBoard[locY+i][locX+i]->team==cteam){
					kingarray[locY+i][locX+i] = 1;
					continue;
			}
			if(GameBoard[locY+i][locX+i]->team!=cteam){
					kingarray[locY+i][locX+i] = 1;
					break;
			}			
		}
	}/*rof*/

	for(i=1;i<8;i++){

		/*checking upper left diagonal */

		if((GameBoard[locY+i][locX-i] == NULL)&&(locY+i<8)&&(locX-i>=0)){
				kingarray[locY+i][locX-i] = 1;
		}
		if((!(GameBoard[locY+i][locX-i]==NULL))&&(locY+i<8)&&(locX-i>=0)){
			if(GameBoard[locY+i][locX-i]->team==cteam){
					kingarray[locY+i][locX-i] = 1;
					continue;
			}
			if(GameBoard[locY+i][locX-i]->team!=cteam){
					kingarray[locY+i][locX-i] = 1;
					break;
			}
				
		}

	}/*rof*/


	for(i=1; i<8;i++){

		/*checking lower right diagonal*/
		if((GameBoard[locY-i][locX+i] == NULL)&&(locY-i>=0)&&(locX+i<8)){
				kingarray[locY-i][locX+i] = 1;
		}
		if((!(GameBoard[locY-i][locX+i]==NULL))&&(locY-i>=0)&&(locX+i<8)){
				if(GameBoard[locY-i][locX+i]->team==cteam){
					kingarray[locY-i][locX+i] = 1;
					continue;
				}
				if(GameBoard[locY-i][locX+i]->team!=cteam){
					kingarray[locY-i][locX+i] = 1;
					break;
				}				
		}

	}


	for(i=0;i<8;i++){

		/*checking lower left diagonal*/
		if((GameBoard[locY-i][locX-i] == NULL)&&(locY-i>=0)&&(locX-i>=0)){
				kingarray[locY-i][locX-i] = 1;
		}
		if((!(GameBoard[locY-i][locX-i]==NULL))&&(locY-i>=0)&&(locX-i>=0)){
				if(GameBoard[locY-i][locX-i]->team==cteam){
						kingarray[locY-i][locX-i] = 1;
						continue;
				}
				if(GameBoard[locY-i][locX-i]->team!=cteam){
						kingarray[locY-i][locX-i] = 1;
						break;
				}
		}

	}

	/* super king knight spaces */
	if ((locY <= 6) && (locX >= 2))
	{
		kingarray[locY+1][locX-2] = 1;
	}
	/* 2 tiles up, 1 tile left */
	if ((locY <= 5) && (locX >= 1))
	{
		kingarray[locY+2][locX-1] = 1;
	}
	/* 2 tiles up, 1 tile right */
	if ((locY <= 5) && (locX <= 6))
	{
		kingarray[locY+2][locX+1] = 1;
	}
	/* 1 tile up, 2 tiles right */
	if ((locY <= 6) && (locX <= 5))
	{
		kingarray[locY+1][locX+2] = 1;
	}
	/* 1 tile down, 2 tiles right */
	if ((locY >= 1) && (locX <= 5) )
	{
		kingarray[locY-1][locX+2] = 1;
	}
	/* 2 tiles down, 1 tile right */
	if ((locY >= 2) && (locX <= 6) )
	{
		kingarray[locY-2][locX+1] = 1;
	}
	/* 2 tiles down, 1 tile left */
	if ((locY >= 2) && (locX >= 1) )
	{
		kingarray[locY-2][locX-1] = 1;
	}
	/* 1 tile down, 2 tiles left */
	if ((locY >= 1) && (locX >= 2) )
	{
		kingarray[locY-1][locX-2] = 1;
	}
}

/* Checks for possible king suicidal moves */
void kingSuicide(t_piece *GameBoard[8][8], int legal[8][8], t_coords coords)
{
	int locY = coords.locY;
	int locX = coords.locX;
	t_piece *cpiece = GameBoard[locY][locX];
	int cteam = cpiece->team;
	int i, j;

	for (j=locY-1; j <= locY+1; j++)
	{
		for (i=locX-2; i <= locX+2; i++)
		{
			if ((i >= 0 && i <= 7) && (j >= 0 && j <= 7) && (i != locX && j != locY))
			{
				if ((legal[j][i]) && (Check(GameBoard,coords,cteam)))
				{
					legal[j][i] = 0;
				}
			}
		}
	}
} /* end of kingSuicide */


/* Check function will also see if any pieces are in the way "PINNED"*/
int Check (t_piece *GameBoard[8][8], t_coords coords, int cteam)
{
	/*can't wait any more nned it for testing*/
	/*hypothetical/current king location*/
	int CHECKED=0;
	int locY=coords.locY;
	int locX=coords.locX;
	t_coords kingloc;
	kingloc.locY=locY;
	kingloc.locX=locX;
	superKing(GameBoard, kingloc, cteam, kArray);
	kArray[locY][locX] = 9;
	printlegal(kArray);
	for (j=0;j<8;j++)
	{
		for (i=0;i<8;i++)
		{	/*Now check if that opponent team piece can kill the king*/
			if ((kArray[j][i] == 1)&&(GameBoard[j][i]!=NULL)&&(GameBoard[j][i]->team != cteam))
			{
			/*skip king's current location*/
			if(!(kArray[j][i]==9))
			{
				/*for bishop, queen*/
				if (((locX-i)==(locY-j))&&((GameBoard[j][i]->points == QUEEN)||(GameBoard[j][i]->points == BISHOP)))
				{
					kArray[j][i]=2;
					/*check along the path*/
					/*from TOP RIGHT*/
					
					if ((kArray[j-1][i-1]==1)||(kArray[j-1][i-1]==9))
					{int u;
						for (u=1;u<8;u++)
						{
							if (kArray[j-u][i-u]==9)
							{CHECKED = 1;break;}
							if (GameBoard[j-u][i+u]==NULL)
							{kArray[j-u][i-u] = 4;}
							else if ((GameBoard[j-u][i-u]!=NULL)&&GameBoard[j-u][i-u]->team == cteam)
							{
								kArray[j-u][i-u] = 3;
								kArray[j][i] = 0;
								break;
							}
						}
					}/*END IF from TOP RIGHT*/
					/*from TOP LEFT*/
					
					if ((kArray[j-1][i+1]==1)||(kArray[j-1][i+1]==9))
					{int u;
						for (u=1;u<8;u++)
						{
							if (kArray[j-u][i+u]==9)
							{CHECKED = 1;break;}
							if (GameBoard[j-u][i+u]==NULL)
							{kArray[j-u][i+u] = 4;}
							else if ((GameBoard[j-u][i+u]!=NULL)&&GameBoard[j-u][i+u]->team == cteam)
							{
								kArray[j-u][i+u] = 3;
								kArray[j][i] = 0;
								break;
							}
						}
					}/*END IF from TOP LEFT*/
					/*from BOTTOM RIGHT*/
					
					if ((kArray[j+1][i-1]==1)||(kArray[j+1][i-1]==9))
					{int u;
						for (u=1;u<8;u++)
						{
							if (kArray[j+u][i-u]==9)
							{CHECKED = 1;break;}
							if (GameBoard[j+u][i-u]==NULL)
							{kArray[j+u][i-u] = 4;}
							else if ((GameBoard[j-u][i-u]!=NULL)&&GameBoard[j+u][i-u]->team == cteam)
							{
								kArray[j+u][i-u] = 3;
								kArray[j][i] = 0;
								break;
							}
						}
					}/*END IF from BOTTOM RIGHT*/
					/*from BOTTOM LEFT*/
					
					if ((kArray[j+1][i+1]==1)||(kArray[j+1][i+1]==9))
					{int u;
						for (u=1;u<8;u++)
						{
							if (kArray[j+u][i+u]==9)
							{CHECKED = 1;break;}
							if (GameBoard[j+u][i+u]==NULL)
							{kArray[j+u][i+u] = 4;}
							else if ((GameBoard[j+u][i+u]!=NULL)&&GameBoard[j+u][i+u]->team == cteam)
							{
								kArray[j+u][i+u] = 3;
								kArray[j][i] = 0;
								break;
							}
						}
					}/*END IF from BOTTOM LEFT*/
				}/*END IF for bishop, queen*/
				/*for rook and queen*/
				if (((locY==j)||(locX==i))&&((GameBoard[j][i]->points == QUEEN)||(GameBoard[j][i]->points == ROOK)))
				{
					kArray[j][i]=2;
					/*in same row*/
					if ((kArray[j][i-1]==1)||(kArray[j][i+1]==1)||(kArray[j][i-1]==9)||(kArray[j][i+1]==9))
					{
						/*from LEFT*/
						if (i<locX)
						{int u;
							for (u=1;u<8;u++)
							{
								if (kArray[j][i+u]==9)
								{CHECKED = 1;break;}
								if (GameBoard[j][i+u]==NULL)
								{kArray[j][i+u] = 4;}
								else if ((GameBoard[j][i+u]!=NULL)&&GameBoard[j][i+u]->team == cteam)
								{
									kArray[j][i+u] = 3;
									kArray[j][i] = 0;
									break;
								}
							}
						}/*END IF from LEFT*/
						/*from RIGHT*/
						if (i>locX)
						{int u;
							for (u=1;u<8;u++)
							{
								if (kArray[j][i-u]==9)
								{CHECKED = 1;break;}
								if (GameBoard[j][i-u]==NULL)
								{kArray[j][i-u]=4;}
								else if ((GameBoard[j][i-u]!=NULL)&&GameBoard[j][i-u]->team == cteam)
								{
									kArray[j][i-u] = 3;
									kArray[j][i] = 0;
									break;
								}
							}
						}/*END IF from RIGHT*/
					}/*END IF in same row*/
					/*in same column*/
					if ((kArray[j-1][i]==1)||(kArray[j+1][i]==1)||(kArray[j-1][i]==9)||(kArray[j+1][i]==9))
					{
						/*from BOTTOM*/
						if (j<locY)
						{int u;
							for (u=1;u<8;u++)
							{
								if (kArray[j+u][i]==9)
								{CHECKED = 1;break;}
								if(GameBoard[j+u][i]==NULL)
								{kArray[j+u][i]=4;}
								else if ((GameBoard[j+u][i]!=NULL)&&GameBoard[j+u][i]->team == cteam)
								{
									kArray[j+u][i] = 3;
									kArray[j][i] = 0;
									break;
								}
							}
						}/*END IF from LEFT*/
						/*from TOP*/
						if (j>locY)
						{int u;
							for (u=1;u<8;u++)
							{
								if (kArray[j-u][i]==9)
								{CHECKED = 1;break;}
								if(GameBoard[j-u][i]==NULL)
								{kArray[j-u][i]=4;}
								else if ((GameBoard[j-u][i]!=NULL)&&GameBoard[j-u][i]->team == cteam)
								{
									kArray[j-u][i] = 3;
									kArray[j][i] = 0;
									break;
								}
							}
						}/*END IF from RIGHT*/
					}/*END IF in same column*/
				}/*END IF for rook and queen*/
				/*for BLACK PAWN*/
				if ((cteam == WHITE)&&(kArray[j-1][i-1]==9))/*white team's turn so check for black pawn*//*from TOP RIGHT*/
				{kArray[j][i]=2;
					CHECKED = 1;
					break;						
				}/*END IF from TOP RIGHT*/
				/*from TOP LEFT*/
				else if ((cteam == WHITE)&&(kArray[j-1][i+1]==9))
				{kArray[j][i]=2;
					CHECKED = 1;break;
				}/*END IF from TOP LEFT*/
				/*for WHITE PAWN*/
				if ((cteam == BLACK)&&(kArray[j+1][i+1]==9))/*white team's turn so check for black pawn*//*from BOTTOM RIGHT*/
				{kArray[j][i]=2;
					CHECKED = 1;
					break;						
				}/*END IF from TOP RIGHT*/
				/*from BOTTOM LEFT*/
				else if ((cteam == BLACK)&&(kArray[j+1][i-1]==9))
				{kArray[j][i]=2;
					CHECKED = 1;break;
				}/*END IF from TOP LEFT*/
				/*for knight*/
				if (GameBoard[j][i]->points == KNIGHT)
				{kArray[j][i]=2;
					CHECKED = 1;break;
				}
			}/*END IF skip king's current location*/
			}/*END IF Now check if that opponent team piece can kill the king*/
		}/*END FOR i*/
	}/*END FOR j*/
printf("KING ARRAY AFTER MODIFIED BY CHECK FUNCTION......CHECKED = %d\n\n",CHECKED);
printlegal(kArray);
/*modify kArray to the agreeded convention*/
for (i=0;i<8;i++)
{	for(j=0;j<8;j++)
	{
		if (kArray[i][j] == 1)
		kArray[i][j] = 0;
		
	}
}
for (i=0;i<8;i++)
{
	for (j=0;j<8;j++)
	{
		if (kArray[i][j] == 4)
		kArray[i][j] = 1;
	}
}
printf("\nKING ARRAY AFTER MODIFIED TO FIT CONVENTION.....CHECKED = %d\n\n",CHECKED);
printlegal(kArray);
return CHECKED;
}

/* Stalemate */
/* returns 1 if there is a stalemate and 0 if there is no stalemate */
int Stalemate(t_piece* GameBoard[8][8], t_coords kingCoords)
{
	int locY = kingCoords.locY;
	int locX = kingCoords.locX;
	t_piece *king = GameBoard[locY][locX];
	int cteam = king->team;
	t_coords coords;
	int legal[8][8];
	int i, j;

	/* check to see if king is in check */
	if (Check(GameBoard,kingCoords,cteam))
	{
		return 0;
	}
	/* if not, check for legal moves */
	else
	{
		for (j=0; j<8; j++)
		{
			for (i=0; i<8; i++)
			{
				/* find a piece that is on the same team as the current player's king */
				if ((GameBoard[j][i]!=NULL)&&(GameBoard[j][i]->team == cteam))
				{
					coords.locX = i;
					coords.locY = j;
					genLegal(coords,GameBoard,legal);

					/* parse through legal array to see if there are any legal moves for the current piece */
					for (j=0; j<8; j++)
					{
						for (i=0; i<8; i++)
						{
							if (legal[j][i])
							{
								return 0;
							}
						}
					}
				}
			}
		}
	}

	/* if it get's through the whole function, then king is not in check */
	/* and there are absolutely no legal moves; therefore, stalemate */
	return 1;
} /* end of Stalemate */

/*#endif*/

/*Checkmate function*/
int Checkmate (int kArray[8][8], t_piece* board[8][8], int cteam, int legal[8][8]) {
	int y, x, v, u;
	t_coords* coords = malloc(sizeof(t_coords));
	/*iterates through board for pieces you have*/
	for (y = 0; y < 8; y++) {
		for (x = 0; x < 8; x++) {
			if (board[y][x] && (board[y][x]->team == cteam)) { /*if its your piece*/
				coords->locY = y;
				coords->locX = x;
				genLegal(*coords, board, legal);
				/*iterates through kArray and checks for legal moves that intersect the generated legal array*/
				for (v = 0; v < 8; v++) {
					for (u = 0; u < 8; u++) {
						/*returns no if there is any intersection*/
						if ((kArray[v][u] == 1 || kArray[v][u] == 2) && (legal[v][u])) {
							free(coords);
							return 0;
						} else {
							continue;
						}
					}
				}
			} else {
				continue;
			}
		}
	}
	free(coords);
	return 1;
}
