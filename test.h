// this function searches for free hexes and saves their coordinates onto the stack
auto* create_possible_movement_coordinates(int** board, const int size) {

    // create a new stack
    auto* possible_movement_coordinates = new stack();

    // iterate through the stack
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            // if the hex is empty (neither red, nor blue) ...
            if (board[i][j] != red_pawn_symbol && board[i][j] != blue_pawn_symbol) {

                // save the coords of it onto the stack
                possible_movement_coordinates->push(UNDEFINED, i, j);

            }
        }
    }

    // return the coords
    return possible_movement_coordinates;

}

// this function checks whose turn it is to place a pawn
bool determine_current_player(int red_pawns_counter, int blue_pawns_counter) {

    // if there are more red player's pawns than the blue one's, it means the blue player now has to place a pawn [ false ]
    if (red_pawns_counter > blue_pawns_counter) return false;

    // otherwise the red player places their pawn
    else return true;

}

// this function adds one more pawn to a generated position
void place_pawn(stack* hexes, int** board, node* possible_movement_coordinates_pair, int* red_pawns_counter, int* blue_pawns_counter, bool current_player) {

    // get the coords
    int x = possible_movement_coordinates_pair->get_position_x();
    int y = possible_movement_coordinates_pair->get_position_y();

    // create a variable that stores the pawn's ascii
    int pawn;

    // if the current player is red [ true ], the pawn is red
    if (current_player) {
        ++(*red_pawns_counter);
        pawn = red_pawn_symbol;
    }

    // otherwise the pawn is blue
    else {
        ++(*blue_pawns_counter);
        pawn = blue_pawn_symbol;
    }

    // place the pawn onto the board
    board[x][y] = pawn;

    node* iterator = hexes->get_head();
    while (iterator != nullptr) {
        if (iterator->get_position_x() == x && iterator->get_position_y() == y) {
            iterator->set_content(pawn);
            break;
        }
        iterator = iterator->get_next();
    }

}

// this function removes an added pawn from the board
void remove_pawn(stack* hexes, int** board, node* possible_movement_coordinates_pair, int* red_pawns_counter, int* blue_pawns_counter) {

    // get the coords
    int x = possible_movement_coordinates_pair->get_position_x();
    int y = possible_movement_coordinates_pair->get_position_y();

    if (board[x][y] == red_pawn_symbol) --(*red_pawns_counter);
    else if (board[x][y] == blue_pawn_symbol) --(*blue_pawns_counter);

    // replace the pawn with a dot [ empty ]
    board[x][y] = default_symbol;

    node* iterator = hexes->get_head();
    while (iterator != nullptr) {
        if (iterator->get_position_x() == x && iterator->get_position_y() == y) {
            iterator->set_content(default_symbol);
            break;
        }
        iterator = iterator->get_next();
    }

}

void launch_board_generator(stack* hexes, int** board, const int size, int* red_pawns_counter, int* blue_pawns_counter, int* number_of_hexes, int tree_depth);

bool minmax(stack* hexes, int** board, const int size, int* red_pawns_counter, int* blue_pawns_counter, int* number_of_hexes, int tree_depth) {

    printf(">>> reds: %d\n"
           "    blues: %d\n\n", *red_pawns_counter, *blue_pawns_counter);

    hexes->print();

    // check if the game is over and if so, return true
    if (check_is_game_over(hexes, blue_pawns_counter, red_pawns_counter, number_of_hexes)) {
        printf(">>> GAME OVER\n\n");
        return true; // TODO: do we need to know WHO won the game?
    }

    // if the maximum tree depth is reached and the game is not over, return false
    if (tree_depth == 0) {
        printf(">>> MAX LEVEL REACHED\n\n");
        return false;
    }

    --tree_depth;

    printf(">>> current tree depth: %d\n\n", tree_depth);

    launch_board_generator(hexes, board, size, red_pawns_counter, blue_pawns_counter, number_of_hexes, tree_depth);

    return false;

}

// this function generates coordinates, boards, and checks a winner
void launch_board_generator(stack* hexes, int** board, const int size, int* red_pawns_counter, int* blue_pawns_counter, int* number_of_hexes, int tree_depth) {

    // create a stack consisting of all coordinates of empty hexes on the board
    auto* possible_movement_coordinates = create_possible_movement_coordinates(board, size);

    // calculate the amount of empty hexes (the ones without a pawn)
    // [ the variable defines how many possibilities there are on each level of the generated tree ]
    const int number_of_empty_hexes = *number_of_hexes - (*red_pawns_counter + *blue_pawns_counter);

    printf(">>> number of empty hexes: %d\n\n", number_of_empty_hexes);

    // get the current player (the one that should now place their pawn)
    bool current_player = determine_current_player(*red_pawns_counter, *blue_pawns_counter);

    printf(">>> current player is ");
    (current_player) ? printf("RED\n\n") : printf("BLUE\n\n");

    // for each pair of possible coordinates ...
    for (int i = 0; i < number_of_empty_hexes; i++) {

        // get a pair of possible coords
        node* possible_movement_coordinates_pair = possible_movement_coordinates->pop();

        printf(">>> checking (%d, %d)\n\n", possible_movement_coordinates_pair->get_position_x(), possible_movement_coordinates_pair->get_position_y());

        // place the current player's pawn onto a board on a generated position
        place_pawn(hexes, board, possible_movement_coordinates_pair, red_pawns_counter, blue_pawns_counter, current_player);

        printf(">>> placed a pawn\n\n");

        printf("THE NEW BOARD: \n\n");
        print_array(board, size);
        printf("------------------------------- \n\n");

        // check is there is a winning path
        minmax(hexes, board, size, red_pawns_counter, blue_pawns_counter, number_of_hexes, tree_depth);

        // clear the board back to the original state
        remove_pawn(hexes, board, possible_movement_coordinates_pair, red_pawns_counter, blue_pawns_counter);

        printf(">>> deleted a pawn\n\n");

        // free memory
        delete possible_movement_coordinates_pair;

    }

}

bool check_can_player_win_in_n_moves(stack* hexes, int blue_pawns_counter, int red_pawns_counter, int number_of_hexes, int tree_depth, bool print_the_result = false) {

    // if the board is not possible, immediately return from the function
    if (!check_is_board_possible(hexes, &blue_pawns_counter, &red_pawns_counter, &number_of_hexes)) {
        if (print_the_result) printf("NO\n\n");
        return false;
    }

    // get the size of the board
    const int size = get_board_size(number_of_hexes);

    // create an array representing the board
    int **board = create_board(hexes, size);

    printf("THE BOARD WE ARE STARTING WITH: \n\n");
    print_array(board, size);
    printf("------------------------------- \n\n");

    tree_depth *= 2;

    launch_board_generator(hexes, board, size, &red_pawns_counter, &blue_pawns_counter, &number_of_hexes, tree_depth);

    return true;

}