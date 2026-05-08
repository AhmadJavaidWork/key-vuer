CC = gcc
CCFlags = -Wall -Wextra -g
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

TARGET = key-veur.o
SRC = src/main.c src/prepareKey.c

all:
	$(CC) $(CFLAGS) $(SRC) -o ${TARGET} ${LDFLAGS}
