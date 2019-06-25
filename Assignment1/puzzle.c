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
    if (read_input(start_board)) {
        board_destroy(goal_board);
        return EXIT_FAILURE;
    }

    if (read_input(goal_board)) {
        board_destroy(start_board);
        return EXIT_FAILURE;
    }

    /* check the two input boards have the correct format */
    if (check_correctness(start_board, goal_board)) {
        printf("checked");
        board_destroy(start_board);
        board_destroy(goal_board);
        return EXIT_FAILURE;
    }

    print_board(start_board, "start");
    print_board(goal_board, "goal");

    /* free all spaces allocated before exit*/
    board_destroy(start_board);
    board_destroy(goal_board);
    return EXIT_SUCCESS;
}