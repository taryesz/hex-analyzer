// this function searches for alternative paths i.e. if the winning player can win multiples times
bool check_for_alternative_paths(int hexes[SIZE][SIZE], bool visited[SIZE][SIZE], const int size, bool* winner, int current_player) {

    // iterate through the whole board
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            // if the current hex is visited ( i.e. is a part of the winning path ) ...
            if (visited[i][j]) {

                // replace it with an empty hex ( i.e. do not consider this hex from now on )
                hexes[i][j] = empty_hex_symbol;

                // create separate arrays to store info about visited hexes of each color
                bool visited_blue_copy[SIZE][SIZE], visited_red_copy[SIZE][SIZE];

                for (int k = 0; k < size; k++) {
                    for (int l = 0; l < size; l++) {
                        visited_blue_copy[k][l] = false;
                        visited_red_copy[k][l] = false;
                    }
                }

                // if the connection between two opposite board edges hasn't been found with the hex replacement ...
                if (!find_connection(hexes, size, winner, visited_blue_copy,visited_red_copy)) {
                    return true; // the board can exist, since there is only one way for the player to connect the edges
                }
                else hexes[i][j] = current_player; // otherwise, place the hex back and continue checking

            }

        }

    }

    // if the program has checked every hex from the winning path and after replacement of each node
    // hasn't lost once, it means that the board cannot exist since there is always an alternative winning path
    // that cannot exist according to the rules of Hex
    return false;

}

// this function checks if the state of a board is possible i.e. if there are multiple winning options for a player
bool check_is_board_possible(int hexes[SIZE][SIZE], const int* blue_pawns_counter, const int* red_pawns_counter, const int* number_of_hexes, bool print_the_result = false) {

    // if the board is not correct, nothing to check, just return NO
    if (!check_is_board_correct(*blue_pawns_counter, *red_pawns_counter, *number_of_hexes)) {
        if (print_the_result) printf("NO\n");
        return false;
    }

    // create a flag that will indicate a winner (if any)
    bool winner;

    // create a flag that will tell the program whether the state of a board is possible or not
    bool is_board_possible;

    // get the board size
    const int size = get_board_size(*number_of_hexes);

    // create a size x size 2D-array of false's to keep track of visited elements:

    bool visited_blue[SIZE][SIZE], visited_red[SIZE][SIZE];

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            visited_blue[i][j] = false;
            visited_red[i][j] = false;
        }
    }

    // create a flag that will indicate whether the game is finished or not
    bool is_game_over = find_connection(hexes, size, &winner, visited_blue, visited_red);

    // if the game is finished ...
    if (is_game_over) {

        // if the winner is the red player ...
        if (winner) {

            // check if the red player has only one possible "winning path"
            is_board_possible = check_for_alternative_paths(hexes, visited_red, size, &winner, red_pawn_symbol);

            // check if the number of pawns of both players are correct and if not, the board cannot exist
            if (*red_pawns_counter <= *blue_pawns_counter) is_board_possible = false;

        }

        // if the winner is the blue player ...
        else {

            // check if the blue player has only one possible "winning path"
            is_board_possible = check_for_alternative_paths(hexes, visited_blue, size, &winner, blue_pawn_symbol);

            // check if the number of pawns of both player are correct and if not, the board cannot exist
            if (*blue_pawns_counter != *red_pawns_counter) is_board_possible = false;

        }

    }

    // if nobody has won yet, the board can exist
    else is_board_possible = true;

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
