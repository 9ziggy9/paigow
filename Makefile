EXE=./main
SRC=main.c
CC=gcc
CFLAGS=-Wall -pedantic -Wconversion -Werror

run: main
	$(EXE)

main:
	$(CC) ./main.c $(CFLAGS) -o $(EXE)

.PHONY: clean
clean:
	rm -rf $(EXE)
