# include "boardADT.h"

int main()
{
    /* initialise start board and goal board, exit if fail*/
    Board_t * start_board = initialise_board();
    if (!start_board) return EXIT_FAILURE;
    
    Board_t * goal_board = initialise_board();
    if (!goal_board) {
        board_destroy(start_board);
        return EXIT_FAILURE;
    }
    
    /* read input from stdin for both boards, exit if bad input read*/
    printf("read 1st board\n");
    if (read_input(start_board)) {
        board_destroy(goal_board);
        return EXIT_FAILURE;
    }
    printf("finished read 1st board\n");

    printf("read 2nd board\n");
    if (read_input(goal_board)) {
        board_destroy(start_board);
        return EXIT_FAILURE;
    }
    printf("finished read 2nd board\n");

    /* check the two input boards have the correct format */
    if (check_correctness(start_board, goal_board)) {
        board_destroy(start_board);
        board_destroy(goal_board);
        return EXIT_FAILURE;
    }
    
    /* get the solvability and print out the results */
    determine_solvability(start_board, goal_board);

    /* free all spaces allocated before exit*/
    board_destroy(start_board);
    board_destroy(goal_board);
    return EXIT_SUCCESS;
}