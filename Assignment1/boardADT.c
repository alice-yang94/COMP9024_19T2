#include "boardADT.h"

/* push new integer tile to the end dynamic array */
static int push(Board_t * board, int tile);

/**
 * A data type Board_t:
 * 1. head is address to start of memory location.
 * 2. curr_offset stores the current offset from head that has been used.
 * 3. size is the total size allocated for board.
*/
typedef struct Board {
    int * head;
    int curr_offset;
    int size;
} Board_t;

/* allocate memory with initial size */
Board_t * initialise_board() {
    Board_t * board = malloc(sizeof(Board_t));
    if (board == NULL) {
        fprintf(stderr, "ERROR: Unable to allocate memory for a new board struct!\n");
        return NULL;
    }

    board->head = malloc(sizeof(int)*INITIAL_SIZE);
    if (board->head == NULL) {
        fprintf(stderr, "ERROR: Unable to allocate memory for a new board!\n");
        return NULL;
    }
    board->curr_offset = INITIAL;
    board->size = INITIAL_SIZE;

    return board;
}

/* read input from stdin to board */
int read_input(Board_t * board) {
    int curr_num = INITIAL;
    char c = getchar();
    while (c != NEWLINE) {
        /* diff in ascii code between digit char and CHAR_ZERO is the digit 
           diff between 'b' and CHAR_ZERO is 50 */
        int digit = c - CHAR_ZERO;
        
        if (isdigit(c)) {
            if (curr_num == INITIAL && digit == INITIAL) {
                /* 0 is not allowed and integer can't start with 0: Error */
                printf("Input Error: Any tile start with 0 is invalid!\n");
                board_destroy(board);
                return EXIT_FAILURE;
            } else {
                curr_num = curr_num * ORDER + digit;
            }

        } else if (c == CHAR_B) {
            if (!curr_num) {
                /* push BLANK to board*/
                if (push(board, BLANK)) {
                    /* if space is used up and can't reallocate, exit failure */
                    return EXIT_FAILURE;
                }
                
            } else {
                /* b is followed by some digits: Error */
                printf("Input Error: A tile cannot mix 'b' and digits!\n");
                board_destroy(board);
                return EXIT_FAILURE;
            }

        } else if (c == SPACE || c == TAB) {
            /* if any whitespaces found, push curr_num to board if it's not 0 */
            if (curr_num){
                if (push(board, curr_num)) {
                    /* if space is used up and can't reallocate, exit failure */
                    return EXIT_FAILURE;
                }
                curr_num = INITIAL;
            }
            /* continue if the previous char is also whitespace... */

        } else {
            printf("\n%c\n", c);
            /* not digit or b or whitespace: Error */
            printf("Input Error: Only b or integers are allowed for a tile!\n");
            board_destroy(board);
            return EXIT_FAILURE;
        }

        /* read next character */
        c = getchar();
    }

    if (curr_num) {
        if (push(board, curr_num)) {
            /* if space is used up and can't reallocate, exit failure */
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

/* push the int tile to the board */
static int push(Board_t * board, int tile) {
    int offset = board->curr_offset;
    int size = board->size;
    
    if (offset == size) {
        /* reallocate board memory spaces with size doubled */
        board->head = realloc(board->head, size * DOUBLE);
        if (!board->head) {
            fprintf(stderr, "ERROR: Unable to reallocate more memory for a the board!\n");
            board_destroy(board);
            return EXIT_FAILURE;
        }
        size = board->size = size * DOUBLE;
    }

    int * curr = board->head + board->curr_offset;
    *curr = tile;
    board->curr_offset++;
    return EXIT_SUCCESS;
}

/* print all tiles in the board in order */
void print_board(Board_t * board, char * board_name) {
    if (board && board->head) {
        int * head = board->head;
        int offset = board->curr_offset;
        printf("%s:", board_name);
        int i;
        for (i = INITIAL; i < offset; i++) {
            int tile = *(head+i);
            if (tile) {
                printf(" %d", tile);
            } else {
                printf(" b");
            }
        }
        printf("\n");
    }
}

int check_board(Board_t * board, char * name) {
    int * head = board->head;
    int length = board->curr_offset;
    /* aim is the desired number, from 0 to length-1;
       j is the searching index for board*/
    int aim, j;
    for (aim = INITIAL; aim < length; aim++) {
        bool found = false;
        for (j = INITIAL; j < length; j++) {
            int curr = *(head+j);
            if (aim == curr) {
                found = true;
                break;
            }
        }

        if (!found) {
            if (aim == INITIAL) {
                printf("Input Error: blank tile is not found in the %s board!\n", name);
            } else {
                printf("Input Error: tile %d is not found in the %s board!\n", aim, name);
            }
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

/* check if the input board is correct */
int check_correctness(Board_t * start_board, Board_t * goal_board) {
    /* check if the start board have a square size*/
    int length = start_board->curr_offset;
    int sqrt_length = sqrt(length);
    if (sqrt_length*sqrt_length != length) {
        printf("Input Error: the start board is not a square!\n");
        return EXIT_FAILURE;
    }

    /* check if the start and goal board have same size */
    if (start_board->curr_offset != goal_board ->curr_offset) {
        printf("Input Error: size of start board and goal board don't match!\n");
        return EXIT_FAILURE;
    }

    if (check_board(start_board, "start") || check_board(goal_board, "goal")) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* free all memory allocated for the given board */
void board_destroy(Board_t* board) {
    if (board) {
        if (board->head) {
            free(board->head);
        }
        free(board);
    }
}