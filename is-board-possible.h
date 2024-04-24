// this function searches for alternative paths i.e. if the winning player can win multiples times
bool check_for_alternative_paths(int** board, bool** visited, const int size, bool* winner, int current_player) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (visited[i][j]) {

                board[i][j] = default_symbol;
                bool **visited_blue_copy = create_array<bool>(size, true, false);
                bool **visited_red_copy = create_array<bool>(size, true, false);

                if (!find_connection(board, size, winner, visited_blue_copy,visited_red_copy)) {
                    free_array(visited_blue_copy, size);
                    free_array(visited_red_copy, size);
                    return true;
                }
                else board[i][j] = current_player;

                free_array(visited_blue_copy, size);
                free_array(visited_red_copy, size);

            }
        }
    }

    return false;

}

// this function checks if the state of a board is possible i.e. if there are multiple winning options for a player
bool check_is_board_possible(stack* hexes, const int* blue_pawns_counter, const int* red_pawns_counter, const int* number_of_hexes, bool print_the_result = false) {

    // if the board is not correct, nothing to check, just return NO
    if (!check_is_board_correct(*blue_pawns_counter, *red_pawns_counter, *number_of_hexes)) {
        if (print_the_result) printf("NO\n");
        return false;
    }

    // get the board size
    const int size = get_board_size(*number_of_hexes);

    // create an array representing the board
    int **board = create_board(hexes, size);

    // create a flag that will indicate a winner (if any)
    bool winner;

    // create a flag that will tell the program whether the state of a board is possible or not
    bool is_board_possible;

    // create a dynamic size x size 2D-array of false's to keep track of visited elements:

    // for the blue pawns
    bool** visited_blue = create_array<bool>(size, true, false);

    // for the red pawns
    bool** visited_red = create_array<bool>(size, true, false);

    // create a flag that will indicate whether the game is finished or not
    bool is_game_over = find_connection(board, size, &winner, visited_blue, visited_red);

    // if the game is finished ...
    if (is_game_over) {

        // if the winner is the red player ...
        if (winner) {

            // check if the red player has only one possible "winning path"
            is_board_possible = check_for_alternative_paths(board, visited_red, size, &winner, red_pawn_symbol);

            // check if the number of pawns of both players are correct and if not, the board cannot exist
            if (*red_pawns_counter <= *blue_pawns_counter) is_board_possible = false;

        }

        // if the winner is the blue player ...
        else {

            // check if the blue player has only one possible "winning path"
            is_board_possible = check_for_alternative_paths(board, visited_blue, size, &winner, blue_pawn_symbol);

            // check if the number of pawns of both player are correct and if not, the board cannot exist
            if (*blue_pawns_counter != *red_pawns_counter) is_board_possible = false;

        }

    }

    // if nobody has won yet, the board can exist
    else is_board_possible = true;

    // free memory
    free_array(board, size);
    free_array(visited_red, size);
    free_array(visited_blue, size);

    // if the result is positive, ( and if the program needs it printed, print it ) return true
    if (is_board_possible) {
        if (print_the_result) printf("YES\n");
        return true;
    }

    // if the result is negative, ( and if the program needs it printed, print it ) return false
    else {
        if (print_the_result) printf("NO\n");
        return false;
    }

}
