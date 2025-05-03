CC = gcc
CFLAGS = -Wall -O2 -pthread
BTREE_SRC = ../db_c/btree.c
BTREE_HDR = ../db_c/btree.h

SRC = server.c register_victim.c $(BTREE_SRC)
OBJ = $(SRC:.c=.o)
TARGET = server

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
