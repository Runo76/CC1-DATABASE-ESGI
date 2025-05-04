CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

SRC = main.c commands.c btree.c
OBJ = $(SRC:.c=.o)
TARGET = db

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
	