CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = db
SRC = main.c table.c btree.c repl.c persistence.c
SRC_TEST = tests/test_btree.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

tests: table.o btree.o persistence.o
	$(CC) $(CFLAGS) -I. $(SRC_TEST) table.o btree.o persistence.o -o tests/test

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) tests/test

