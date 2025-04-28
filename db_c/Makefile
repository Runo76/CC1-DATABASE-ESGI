CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

SRC = main.c commands.c btree.c
OBJ = $(SRC:.c=.o)
TARGET = db

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /f /q $(OBJ) $(TARGET).exe
	