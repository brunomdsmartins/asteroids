CC = gcc

CFLAGS = -Wall -Wextra -Werror -Iinclude
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = $(wildcard src/*.c) main.c

TARGET = game

clean:
	rm -f $(TARGET)

build:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run:
	./$(TARGET)

all: clean build run
