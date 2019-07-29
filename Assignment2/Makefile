CC = gcc
CFLAGS = -O -Wall -Werror

# syntax: 
# $ gcc -Olevel [options] [source files] [object files] [-o output file]
# https://www.rapidtables.com/code/linux/gcc/gcc-o.html#output%20file
differ: differByOne.c differByOne.h
	$(CC) $(CFLAGS) differByOne.c -o differ

.PHONY: clean
clean:
	rm -f differ *.o