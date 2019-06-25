CC = gcc
CFLAGS = -I.
DEPS = boardADT.h
OBJ = puzzle.o boardADT.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

puzzle: $(OBJ)
	$(CC) -o $@  $(OBJ)

.PHONY: clean
clean:
	rm -f puzzle $(OBJ) *.o