EXE=./main
SRC=main.c
CC=gcc
CFLAGS=-Wall -pedantic -Wconversion -Werror
OBJS=tiles.o

run: main
	$(EXE)

main: tiles.o main.c
	$(CC) ./main.c $(CFLAGS) -o $(EXE) $(OBJS)

tiles.o: tiles.c
	$(CC) $(CFLAGS) -c tiles.c

.PHONY: clean
clean:
	rm -rf $(EXE) $(OBJS)
