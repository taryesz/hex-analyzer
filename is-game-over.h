// this function looks for connections between board edges
bool traverse_board(int** board, bool** visited, int x, int y, int size, int current_player, int opposite_player) {

    // if the symbol that is being currently checked either doesn't exist because of non-existent coordinates
    // or the symbol was already visited (i.e. taken into account earlier), or the symbol is a pawn of the opposite player,
    // ignore this symbol
    if (x < OUT_OF_BOUNDS_COORDINATE || x >= size || y < OUT_OF_BOUNDS_COORDINATE || y >= size || visited[x][y] || board[x][y] != current_player) return false;

    // create a variable that will store the max possible coord which doesn't make it to out-of-bounds of the board
    // i.e. since arrays start counting from 0, the program has to decrement the size by 1
    const int max_coord = size - OFFSET_FROM_BOARD_EDGE;

    // if the algorithm made it to the opposite side of the array ...
    // [ for the blue player the program checks the left and right sides, so it's interested in X-axis ]
    // [ for the red player the program checks the top and bottom sides, so it's interested in Y-axis ]
    // the axes are inverted because the array representing the board is mirrored
    if ((current_player == blue_pawn_symbol && y == max_coord) || (current_player == red_pawn_symbol && x == max_coord)) {
        visited[x][y] = true;
        return true;
    }

    // if the current symbol is representing this same player, but it's not at the opposite edge,
    // it's somewhere in the middle then, so mark it as visited
    visited[x][y] = true;

    // check the current symbol's neighbors
    return (traverse_board(board, visited, x, y - NEIGHBOR_DISTANCE, size, current_player, opposite_player) ||
            traverse_board(board, visited, x, y + NEIGHBOR_DISTANCE, size, current_player, opposite_player) ||
            traverse_board(board, visited, x + NEIGHBOR_DISTANCE, y, size, current_player, opposite_player) ||
            traverse_board(board, visited, x - NEIGHBOR_DISTANCE, y, size, current_player, opposite_player) ||
            traverse_board(board, visited, x + NEIGHBOR_DISTANCE, y + NEIGHBOR_DISTANCE, size, current_player, opposite_player) ||
            traverse_board(board, visited, x - NEIGHBOR_DISTANCE, y - NEIGHBOR_DISTANCE, size, current_player, opposite_player));

}

// this function checks the pawns on the board edges and looks for the connections between board edges
bool launch_traverse_on_board_edge(int** board, bool** visited, int x, int y, int current_player, int opposite_player, const int size, bool* winner) {

    // if the symbol is a pawn and if the connection between edges made from the same kind of pawns is found ...
    if (board[x][y] == current_player && traverse_board(board, visited, x, y, size, current_player, opposite_player)) {

        // set the winner
        // if the path is for the red player, set to true
        if (current_player == red_pawn_symbol) *winner = true;

        // if the path is for the blue player, set to false
        else *winner = false;

        // return true which means the path was found, the game is over
        return true;

    }

    // if no connections are found, the game is not over yet
    else return false;

}

// this function checks if one of the player has connected their edges with pawns
bool find_connection(int** board, const int size, bool* winner, bool** visited_blue, bool** visited_red) {

    // create a variable that will store the permanent index of an element
    // *** along the edge of the board ***
    // [ blue player --- left & right edge, so 0 will be set for Y-axis ]
    // [ red player  --- top & bottom edge, so 0 will be set for X-axis ]
    // *** the axes are mirrored because the array is too ***
    const int edge_symbol_mark = 0;

    // launch the board traversal looking for 'r' connecting the opposite board's sides
    for (int i = 0; i < size; i++) {

        // if an 'r' was found along the edge and the connection to the opposite edge is found too, then the game is over
        if (launch_traverse_on_board_edge(board, visited_red, edge_symbol_mark, i, red_pawn_symbol, blue_pawn_symbol, size, winner)) {
            return true;
        }

        // if an 'b' was found along the edge and the connection to the opposite edge is found too, then the game is over
        if (launch_traverse_on_board_edge(board, visited_blue, i, edge_symbol_mark, blue_pawn_symbol, red_pawn_symbol, size, winner)) {
            return true;
        }

    }

    return false;

}

// this function creates all necessary variables for the board traversal and returns the result of it
bool check_is_game_over(stack* hexes, const int* blue_pawns_counter, const int* red_pawns_counter, const int* number_of_hexes, bool print_the_result = false) {

    // if the board is not correct, nothing to check, just return NO
    if (!check_is_board_correct(*blue_pawns_counter, *red_pawns_counter, *number_of_hexes)) {
        if (print_the_result) printf("NO\n");
        return false;
    }

    // get the size of the board
    const int size = get_board_size(*number_of_hexes);

    // create an array representing the board
    int **board = create_board(hexes, size);

    // create a flag that will indicate the winner (if any)
    bool winner;

    // create a dynamic size x size 2D-array of false's to keep track of visited elements:

    // for the blue pawns
    bool** visited_blue = create_array<bool>(size, true, false);

    // for the red pawns
    bool** visited_red = create_array<bool>(size, true, false);

    // if the game was finished, return YES and the information about the winner
    bool result = find_connection(board, size, &winner, visited_blue, visited_red);

    // free memory
    free_array(board, size);
    free_array(visited_blue, size);
    free_array(visited_red, size);

    // if the result is positive, ( and if the program needs it printed, print it ) return true
    if (result) {
        if (print_the_result) {
            printf("YES ");
            (winner) ? printf("RED\n") : printf("BLUE\n"); // print who won the game
        }
        return true;
    }

    // if the result is negative, ( and if the program needs it printed, print it ) return false
    else {
        if (print_the_result) printf("NO\n");
        return false;
    }

}
