EXE=./main
SRC=main.c
CFLAGS=-Wall -pedantic -Wconversion -Werror

run: main
	$(EXE)

main:
	cc ./main.c $(CFLAGS) -o $(EXE)

.PHONY: clean
clean:
	rm -rf $(EXE)
