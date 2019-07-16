CC = gcc
CFLAGS = -I.
DEPS = boardADT.h
OBJ = puzzle.o boardADT.o

# The rule says:
# 1. The .o file depends upon the .c version of the file and the .h files in the DEPS macro
# 2. To generate the .o file, make needs to compile the .c file using the compiler defined in the CC macro
# 3. The -c flag says to generate the object file
# 4. the -o $@ says to put the output of the compilation in the file named on the left side of the :
# 5. the $< is the first item in the dependencies list
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

puzzle: $(OBJ)
	$(CC) -o $@  $(OBJ)

.PHONY: clean
clean:
	rm -f puzzle $(OBJ) *.o