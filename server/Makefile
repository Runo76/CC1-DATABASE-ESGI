BTREE_SRC = ../BTreeDB/btree.c ../BTreeDB/persistence.c ../BTreeDB/table.c
BTREE_HDR = ../BTreeDB/btree.h ../BTreeDB/persistence.h ../BTreeDB/table.h

SRC = server.c register_victim.c $(BTREE_SRC)
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -O2 -pthread

TARGET = server

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

