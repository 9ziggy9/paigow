EXE=./main
DEPS=tiles.c analysis.c
OBJS=$(DEPS:.c=.o)
CC=gcc
CFLAGS=-Wall -pedantic -Wconversion -Werror

run: main
	$(EXE)

main: $(OBJS) main.c
	$(CC) ./main.c $(CFLAGS) -o $(EXE) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -rf $(EXE) $(OBJS)
