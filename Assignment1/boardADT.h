#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define true 1
#define false 0

#define NEWLINE '\n'
#define SPACE ' '
#define TAB '\t'
#define CHAR_ZERO '0'
#define INITIAL 0
#define DOUBLE 2
#define ORDER 10

/* In order to store the board with all integer, 0 is used to represent BLANK */
#define BLANK 0
#define CHAR_B 'b'

/* enough for a 10*10 puzzle */
#define INITIAL_SIZE 100

/**
 * A structure Board, stores tiles in a dynamic array.
*/
typedef struct Board Board_t;

typedef int bool;

/* Allocate memory spaces for a new board */
Board_t * initialise_board();

/* Read input from stdin */
int read_input(Board_t * board);

/* Print board */
void print_board(Board_t * board, char * board_name);

/* Check if the given board has the current input format. */
int check_correctness(Board_t * start_board, Board_t * goal_board);

/* Determine if the goal_board is reachable from the start_board. */
int determine_solvability(Board_t * start_board, Board_t * goal_board);

/* Destroy the given board and free the allocated spaces*/
void board_destroy(Board_t* board);


