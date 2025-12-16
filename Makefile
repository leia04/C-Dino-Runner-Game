CC=gcc
CFLAGS=-Wall -Wextra -O2 -Iinclude
LDFLAGS=-lncurses
TARGET=dino_game

SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)
