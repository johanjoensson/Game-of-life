CC = gcc
CFLAGS = -Wall -Wextra -W -pedantic -std=c99 -g
BIN = bin
SRC = src
LDFLAGS = -lSDL -I/usr/include/SDL -lncurses



OBJ = $(BIN)/game.o\
      $(BIN)/congame.o\
      $(BIN)/print_nc.o

EXE = game\

all:$(EXE) 

$(BIN)/%.o : $(SRC)/%.c
	$(CC) -c $(CFLAGS) $? $(LDFLAGS) -o $@

# sample: sample.o
# 	$(CC) $(CFLAGS) $(SRC)/$? $(LDFLAGS) -o $@

game:   $(OBJ)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@


clean:
	rm  game $(BIN)/*.o

cleanall:
	rm $(EXE) $(BIN)/$(OBJ)
