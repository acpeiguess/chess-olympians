/*
 * Team 2 / Milk N Dim Sum
 * IO.c
 */

/*************************************** Notes **********************************************
 * 1/17/2014 - Bruce Liu - Created module and declared basic print functions
 * 
 * *********************************** End Notes ********************************************/

#include "../inc/IO.h"

#define IODEBUG 0

/* Prints board */
void printBoard(t_piece* gameboard[8][8]){
  
  char t;
  char c;
  int i, j;
  
  for(i=0;i<8;i++){
    printf("  +----+----+----+----+----+----+----+----+");
    printf("\n");
    for(j=0;j<8;j++){
      if(j == 0){
	printf("%d | ", 8-i);
      }
      else{
	printf(" | ");
      }
      if(gameboard[7-i][j]==NULL){
	printf("  ");
              }
      else{
	t= getPTypeChar(gameboard[7-i][j]);
      	c= getPieceColorChar(gameboard[7-i][j]);
	printf("%c%c",c,t);

	}
      }
    printf(" |");
    printf("\n");
    }
  printf("  +----+----+----+----+----+----+----+----+\n"
         "    A    B    C    D    E    F    G    H   \n");
  printf("\n\n");
}

/* returns string associated with piecetype */
char getPTypeChar(t_piece  *piece){
  switch( piece->points)
    {
    case KING:
      return 'K';
    case QUEEN:
      return 'Q';
    case BISHOP:
      return 'B';
    case KNIGHT:
      return 'N';
    case ROOK:
      return 'R';
    case PAWN:
      return 'P';
    default: /* This case should never happen */
      return 'e';
    }
    
}

/* returns string associated with team color */
char getPieceColorChar(t_piece *piece){
  switch(piece->team)
    {
    case BLACK:
      return 'b';
    case WHITE:
      return 'w';
    default: /* This case should never happen */
      return 't';
    }

}

/* Prints Main Menu */
void printMainMenu(){
  printf(" \n          " 
"\n           =   :   =                   " 
"\n       =   ==+:~ ====  =               " 
"\n        =+++~=~=~====,=:               " 
"\n         ==++:+:~~~~=~==               " 
"\n        =++~+=~====~===,               " 
"\n         :+=~+=~+=~:~=:+~              " 
"\n       ++===~~==~~++++~=               " 
"\n           ~I=?+~I=I:+~                " 
"\n           +=~~III?~7~+=               " 
"\n           ~   7II7I7, ::              " 
"\n           =+~  7I=I+== +~:            " 
"\n            =~~:==+:~:~=  =~==.        " 
"\n              ++:~~~~??=~~, .          " 
"\n          .~==:?:~:=~,:I=??+           " 
"\n            =~+:+,,===~?+I777          " 
"\n           ??++=~~~==+=~==I77I?        " 
"\n         .7II?::==???+=:=   ==?        " 
"\n    ,?+=?II7  :,++++==:   =+:=I        " 
"\n  .+~?7~=I?   ~+~=7====   ~:~~==       " 
"\n  +?~~+~   I+~,?+,:+~II+ ~+~=~~        " 
"\n   ++++    7~:I,~,:?+?:=?+7,           " 
"\n      =   ==+~~:+=~++:,=~II?+          " 
"\n      ~,  :I=~+~+::7~+=:,=+            " 
"\n      I?++II~=+~~+I~~~7?~:+=           " 
"\n     .~,~+??I+I+?=:~+~::+=+=I~         " 
"\n       I~:+=~~==+=:=~I=+:~?+~          " 
"\n        ?=+=:~,+==+++++:,~=I+?         " 
"\n        ==:~::====  +??+==~~++?        " 
"\n    ++7=7=,?+==?  ?++I,~,,+~+          "
"\n       ?I~:=~??=.?~, .++?.~~+?++=      " 
"\n      +?++I=7++~ =?=  ~+++++++++=+     " 
"\n      +?=+=I===   ~:  +,==+=++=+++=.   " 
"\n     +++=?+:=?,        +~=++?+====+=   " 
"\n    ?++:=+++7+?        +=========:=~   " 
"\n   ~=~~~+++==+=          +~~===+~===   " 
"\n    =~++++~~:~+I          =~=+I?~+++:  " 
"\n    :7==~I==, I=            ++~~+++~~  " 
"\n     ++.===+.  ~7           +~:~:~~    " 
"\n     ==~,=,,   +=.             +~~=    " 
"\n     7=:: :     I:              ==~    " 
"\n    ==~:=        ::             +~::   " 
"\n:++~:~~=~         +             :~~==  "
"\n ,:::                           ~~==::~"
"\n\n\n");
  printf("1. Human vs Human \n"
         "2. Human vs Computer \n"
	 "3. Custom Board Setup \n"
	 "0. Exit \n\n");
  
}

/* Prints Game Menu */
void printGameMenu(){
  
  printf("To Make move      : Type the Move\n"
         "To Undo move type : Undo\n"
	 "To quit type      : Quit \n\n");
  printf("What do you want to do : ");
  
}

/* Get Integer */
int getInt(char* message){
  
  int var;
  printf("%s", message); scanf("%d", &var);
  return var;
  
}

/* Get Move */
void getMove(char* move){
  
  printf("\nPlease enter a move: ");
  scanf("%s", move);
  if(IODEBUG){
    printf("Recorded move in function: %s\n", move);
  }
  
}

/* Decode Move: will return 1 if valid coords are decoded. returns 0 if invalid move is decoded */
int decodeMove (char* move, t_coords *from, t_coords *to, t_piece *board[8][8], int team){
  
  int i = 0;
  int coordinates[4] = {0};
  int validcoords = 1;
  
  for(i=0; i<4; i++){
    
    if(i%2 == 0){
      /* A-H is being eval'd */
      coordinates[i] = toUpper(move[i]) - 'A';
      if(EnsureNumber(coordinates[i],0,7) != 1){
	printf("\n Move input invalid ONE! \n");
	validcoords = 0;
	break;
      }
    }
    else{
      /* 0-7 is being eval'd */
      coordinates[i] = move[i] - '1';
      if(EnsureNumber(coordinates[i],0,7) != 1){
	printf("\n Move input invalid TWO! \n");
	validcoords = 0;
	break;
      }
    }
    
    if(IODEBUG && i!=4){
      
      printf("coordinates[%d]: %30d\n", i, coordinates[i]);
      
    }
  }

  if (checkLoc(board, coordinates[1], coordinates[0], team))
	{
		validcoords = 1;
	}
  else 
	{
		validcoords = 0;
	}
  
  if(validcoords){
    
    from->locX = coordinates[0];
    from->locY = coordinates[1];
    to->locX = coordinates[2];
    to->locY = coordinates[3];
    return checkLoc2(to);
  }
  else{
    return 0;
  }
  
}

/* Returns upper case char when lower/upper case char is given */
char toUpper(char letter){
  
  char upper;
  
  if(IODEBUG){
    printf("letter: %30c\n", letter);
    
  }
  
  /* 122 is 'z' and 97 is 'a' on ascii table */
  if((letter >= 'a') && (letter <= 'z')){
    
    if(IODEBUG){
      printf("Inside toupper if statement...\n\n");
    
    }
    upper = letter - 32; /* since 'a' is 97 and 'A' is 65 on ascii table */
    return upper;
    
  }
  else{
    /* original char was returned */
    if(IODEBUG){
      printf("Returning original letter...\n\n");
    
    }
    return letter;
    
  }
  
}

/* verifies that value is within desired range of numbers */
int EnsureNumber(int value, int botRange, int topRange){
  
    if((value < botRange) || (value > topRange)){
      /* value is outside range */
        return 0;
    }
    else{
      /* value is inside range */
        return 1;
    }
}
