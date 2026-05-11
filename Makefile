CC = clang 
CCFlags = -std=c99 -D_DEFAULT_SOURCE -Wall -Wextra -g -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -fsanitize=address -fsanitize=undefined
LDFLAGS = -fsanitize=address -fsanitize=undefined -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

TARGET = key-veur.o
SRC = src/main.c src/prepareKey.c

all:
	$(CC) $(CFLAGS) $(SRC) -o ${TARGET} ${LDFLAGS}

clean:
	rm -rf ${TARGET}
