CC = gcc
CFLAGS = -Wall -Wextra -W -pedantic -std=c99 -g
BIN = bin
SRC = src
LDFLAGS = -lSDL -I/usr/include/SDL -lncurses


SOURCES = $(wildcard $(SRC)/*.c)

OBJ = $(patsubst $(SRC)/%.c, $(BIN)/%.o, $(SOURCES))

EXE = 	game\

.PHONY: bindir srcdir
all: bindir srcdir $(EXE) 

bindir:
	mkdir -p bin

srcdir:
	mkdir -p src

$(BIN)/%.o : $(SRC)/%.c
	$(CC) -c $(CFLAGS) $? -o $@


game:   $(OBJ)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@


clean:
	rm  game $(BIN)/*.o

cleanall:
	rm $(EXE) $(BIN)/$(OBJ)
