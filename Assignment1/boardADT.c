#include "boardADT.h"

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

/* push new integer tile to the end dynamic array */
static int push(Board_t * board, int tile);

/* check if each board is valid with truth board */
static int check_board(Board_t * board, char * name);

/* check if the board is valid without extra memory spaces */
static int check_board_naive(Board_t * board, char * name);

/* calculate board disorder */
static int calculate_disorder(Board_t * board);

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

    /* true if previous char is b, used to determine the case like digits followed by b */
    bool prev_b = false;

    while (c != NEWLINE && c != EOF) {
        /* diff in ascii code between digit char and CHAR_ZERO is the digit 
           diff between 'b' and CHAR_ZERO is 50 */
        int digit = c - CHAR_ZERO;
        
        if (isdigit(c)) {
            if (curr_num == INITIAL && digit == INITIAL) {
                /* 0 is not allowed and integer can't start with 0: Error */
                printf("Input Error: Any tile start with 0 is invalid!\n");
                board_destroy(board);
                return EXIT_FAILURE;
            } else if (prev_b) {
                /* digits are not allowed to followed by b */
                printf("Input Error: A tile cannot mix 'b' and digits!\n");
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
                
                prev_b = true;

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
            prev_b = false;
            /* continue if the previous char is also whitespace... */

        } else {
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
        /* reallocate board memory spaces with size + initialsize */
        int* newhead = realloc(board->head, (size + INITIAL_SIZE)*sizeof(int));
        if (!newhead) {
            fprintf(stderr, "ERROR: Unable to reallocate more memory for a the board!\n");
            board_destroy(board);
            return EXIT_FAILURE;
        }
        board->head = newhead;
        board->size = size + INITIAL_SIZE;
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

/* check if the board has tiles: blank(0) and 1..size-1 with n^2 complexity*/
static int check_board_naive(Board_t * board, char * name) {
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

/* check if the board has tiles: blank(0) and 1..size-1 using a truth board*/
static int check_board(Board_t * board, char * name) {
    int * head = board->head;
    int length = board->curr_offset;

    /* initialise a truth board with all 0 */
    int * truth_board = calloc(length, sizeof(int));
    if (!truth_board) {
        /* if unable to allocate memory for truth board, do it with naive checking*/
        return check_board_naive(board, name);
    }

    /* updating the truth board cell with true if a number is found */
    int i;
    for (i = 0; i < length; i++) {
        int curr_num = *(head+i);
        if (curr_num < 0 || curr_num >= length) {
            printf("Input Error: tile %d in the %s board is out of range!\n", curr_num, name);
            free(truth_board);
            return EXIT_FAILURE;
        }
        *(truth_board + curr_num) = true;
    }

    /* if the truth board has any false values, the input is incorrect */
    if (!*truth_board) {
        printf("Input Error: blank tile is not found in the %s board!\n", name);
        free(truth_board);
        return EXIT_FAILURE;
    }

    for (i = 1; i < length; i++) {
        if (!*(truth_board + i)) {
            printf("Input Error: tile %d is not found in the %s board!\n", i, name);
            free(truth_board);
            return EXIT_FAILURE;
        }
    }
    free(truth_board);
    return EXIT_SUCCESS;
}

/* check if the input board is correct */
int check_correctness(Board_t * start_board, Board_t * goal_board) {
    /* the smallest board is 2*2 which has length 4 */
    int length = start_board->curr_offset;
    if (length < 4) {
        printf("Input Error: the board size can't be smaller than 2*2!\n");
        return EXIT_FAILURE;
    }
    
    /* check if the start board have a square size*/
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

/* calculate the board disorder by summing the disorders of each tile, 
*   return 0 for even parity, 1 for odd parity.
*/
static int calculate_disorder(Board_t * board) {
    int * head = board->head;
    int length = board->curr_offset;
    int sqrt_len = (int) sqrt(length);

    int i, j;
    int board_disorder = INITIAL;

    for (i = INITIAL; i < length; i++) {
        int curr_tile = *(head+i);
        int curr_disorder = INITIAL;

        if (curr_tile == BLANK) {
            if (length%DOUBLE == INITIAL) {
                /* if board has even length, add row number of blank tile to disorder */
                board_disorder += (int) (i/sqrt_len) + 1;
            }
        } else {
            for (j = i; j < length; j++) {
                int tile_behind = *(head+j);
                if (tile_behind < curr_tile && tile_behind != BLANK) {
                    curr_disorder++;
                }
            }
        }
        board_disorder += curr_disorder;
    }
    
    return board_disorder%DOUBLE == INITIAL;
}

/* determine if goal board is reachable from start board, true for reachable */
int determine_solvability(Board_t * start_board, Board_t * goal_board) {
    return calculate_disorder(start_board) == calculate_disorder(goal_board);
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