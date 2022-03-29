#Chess Makefile
#Team2 / Milk & Dim Sum

#variables
CC        = gcc
DEBUG     = -g -DDEBUG
DNDEBUG   = 
SDL_LFLAGS  = $(shell sdl-config --libs)
SDL_CFLAGS  = $(shell sdl-config --cflags)
FLAGS     = -Wall -ansi
CFLAGS    = -Wall -ansi -c
#SDIR is used to determine the location of source files
SDIR      = src/
#BDIR is used to determine a target binary location
BDIR      = bin/
#ODIR is used to determine a target location for object files
ODIR      = obj/
#IDIR is used to determine a target location for header files
IDIR      = inc/
#TDIR is used to determine a target location for test files
TDIR      = test/

_OBJ      = IO.o Pieces.o Board.o Rules.o AI.o
OBJ       = $(patsubst %, $(ODIR)%, $(_OBJ))
_OBJT     = main_t.o IO_t.o Pieces_t.o Board_t.o Rules_t.o AI_t.o
OBJT      = $(patsubst %, $(ODIR)%, $(_OBJT))


_SRC      = main.c IO.c Pieces.c Board.c Rules.c AI.c
SRC       = $(patsubst %, $(SDIR)%, $(_SRC))
_SRCT     = test_interface.c test_boarddisplay.c test_rulecheck.c
SRCT      = $(patsubst %, $(TDIR)%, $(_SRCT))

_INC      = IO.h Pieces.h Board.h Rules.h AI.h
INC       = $(patsubst %, $(IDIR)%, $(_INC))

all: chess

chess_console: $(_OBJ) main.o
	$(CC) $(FLAGS) $(DNDEBUG) $(OBJ) $(ODIR)main.o -o $(BDIR)chess_console
	
main.o: $(SRC) $(INC)
	$(CC) $(CFLAGS) $(DNDEBUG) $(SDIR)main.c -o $(ODIR)main.o
	
Pieces.o: $(SRC) $(INC)
	$(CC) $(CFLAGS) $(DNDEBUG) $(SDIR)Pieces.c -o $(ODIR)Pieces.o
	
IO.o: $(SRC) $(INC)
	$(CC) $(CFLAGS) $(DNDEBUG) $(SDIR)IO.c -o $(ODIR)IO.o
	
Board.o: $(SRC) $(INC)
	$(CC) $(CFLAGS) $(DNDEBUG) $(SDIR)Board.c -o $(ODIR)Board.o

Rules.o: $(SRC) $(INC)
	$(CC) $(CFLAGS) $(DNDEBUG) $(SDIR)Rules.c -o $(ODIR)Rules.o

AI.o: $(SRC) $(INC)
	$(CC) $(CFLAGS) $(DNDEBUG) $(SDIR)AI.c -o $(ODIR)AI.o

#The following make commands enable debug for testing.
	
test: $(_OBJT)
	$(CC) $(FLAGS) $(DEBUG) $(OBJT) -o $(BDIR)test
	
main_t.o: $(SRC) $(INC) $(SRCT)
	$(CC) $(CFLAGS) $(DEBUG) $(TDIR)test_interface.c -o $(ODIR)main_t.o
	
Pieces_t.o: $(SRC) $(INC) $(SRCT)
	$(CC) $(CFLAGS) $(DEBUG) $(SDIR)Pieces.c -o $(ODIR)Pieces_t.o
	
IO_t.o: $(SRC) $(INC) $(SRCT)
	$(CC) $(CFLAGS) $(DEBUG) $(TDIR)test_boarddisplay.c -o $(ODIR)IO_t.o
	
Board_t.o: $(SRC) $(INC) $(SRCT)
	$(CC) $(CFLAGS) $(DEBUG) $(SDIR)Board.c -o $(ODIR)Board_t.o

Rules_t.o: $(SRC) $(INC) $(SRCT)
	$(CC) $(CFLAGS) $(DEBUG) $(TDIR)test_rulecheck.c -o $(ODIR)Rules_t.o

AI_t.o: $(SRC) $(INC) $(SRCT)
	$(CC) $(CFLAGS) $(DEBUG) $(TDIR)AI.c -o $(ODIR)AI_t.o

#chess gui menu output only

chess: chessgui.o GUI.o $(_OBJ)
	$(CC) $(DNDEBUG) $(ODIR)chessgui.o $(ODIR)GUI.o $(OBJ) $(FLAGS) $(SDL_LFLAGS) -o $(BDIR)chess
	ln -s bin/chess .
	
chessgui.o: $(SDIR)ChessMenu.c $(SDIR)GUI.c $(IDIR)GUI.h $(SRC) $(INC)
	$(CC) $(DNDEBUG) $(SDIR)ChessMenu.c $(CFLAGS) -o $(ODIR)chessgui.o $(SDL_CFLAGS)
	
GUI.o: $(SDIR)GUI.c $(IDIR)GUI.h $(SRC) $(INC)
	$(CC) $(DNDEBUG) $(SDIR)GUI.c -o $(ODIR)GUI.o $(CFLAGS) $(SDL_CFLAGS)

clean:
	rm -f $(ODIR)*.o $(BDIR)chess $(BDIR)test $(BDIR)chess_console GameLog.txt chess

remake: clean chess
