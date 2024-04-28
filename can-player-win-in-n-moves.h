int max(int a, int b) {
    if (a > b) return a;
    else if (b > a) return b;
    else return a;
}

int min(int a, int b) {
    if (a < b) return a;
    else if (b < a) return b;
    else return a;
}

// this function determines if the current level of the tree has to return the best or worst result
bool check_maximizing(int main_player, int current_player) {

    if (main_player == blue_pawn_symbol) {
        if (current_player) return true;  // if the checked player is different from the current one, the max-move is made
        else return false;                // if both players are the same, the min-move is made
    }
    else {
        if (current_player) return false; // if the checked player is the same as the current one, the max-move is made
        else return true;                 // if the checked player is different from the current one, the max-move is made
    }

}

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
void place_pawn(stack* hexes, int** board, node* possible_movement_coordinates_pair, int* red_pawns_counter, int* blue_pawns_counter, bool current_player, int* placed_red_pawns_counter, int* placed_blue_pawns_counter) {

    // get the coords
    int x = possible_movement_coordinates_pair->get_position_x();
    int y = possible_movement_coordinates_pair->get_position_y();

    // create a variable that stores the pawn's ascii
    int pawn;

    // if the current player is red [ true ], the pawn is red
    if (current_player) {
        ++(*red_pawns_counter);
        ++(*placed_red_pawns_counter);
        pawn = red_pawn_symbol;
    }

    // otherwise the pawn is blue
    else {
        ++(*blue_pawns_counter);
        ++(*placed_blue_pawns_counter);
        pawn = blue_pawn_symbol;
    }

    // place the pawn onto the board
    board[x][y] = pawn;

    // add the pawn to the stack of pawns
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
void remove_pawn(stack* hexes, int** board, node* possible_movement_coordinates_pair, int* red_pawns_counter, int* blue_pawns_counter, int* placed_red_pawns_counter, int* placed_blue_pawns_counter) {

    // get the coords
    int x = possible_movement_coordinates_pair->get_position_x();
    int y = possible_movement_coordinates_pair->get_position_y();

    if (board[x][y] == red_pawn_symbol) {
        --(*red_pawns_counter);
        --(*placed_red_pawns_counter);
    }
    else if (board[x][y] == blue_pawn_symbol) {
        --(*blue_pawns_counter);
        --(*placed_blue_pawns_counter);
    }

    // replace the pawn with a dot [ empty ]
    board[x][y] = empty_hex_symbol;

    // delete the pawn from the stack
    node* iterator = hexes->get_head();
    while (iterator != nullptr) {
        if (iterator->get_position_x() == x && iterator->get_position_y() == y) {
            iterator->set_content(empty_hex_symbol);
            break;
        }
        iterator = iterator->get_next();
    }

}

bool launch_board_generator(stack* hexes, int** board, int size, int* red_pawns_counter, int* blue_pawns_counter, int* number_of_hexes, int tree_depth, int main_player, bool perfect_opponent, int number_of_moves, int* placed_red_pawns_counter, int* placed_blue_pawns_counter, int alpha, int beta);

int minmax(stack* hexes, int** board, const int size, int* red_pawns_counter, int* blue_pawns_counter, int* number_of_hexes, int tree_depth, int main_player, bool perfect_opponent, int number_of_moves, int* placed_red_pawns_counter, int* placed_blue_pawns_counter, int alpha, int beta) {

    bool winner;

    // check if the game is finished ...
    if (check_is_game_over(hexes, blue_pawns_counter, red_pawns_counter, number_of_hexes, &winner, false)) {

        // if the checked player won ...
        if ((main_player == red_pawn_symbol && winner) || (main_player == blue_pawn_symbol && !winner)) {

            // check if the amount of placed pawns corresponds to the amount of moves the player is allowed to make
            if (main_player == red_pawn_symbol) {
                if (*placed_red_pawns_counter >= number_of_moves) return POSITIVE_RESULT;
            }
            else {
                if (*placed_blue_pawns_counter >= number_of_moves) return POSITIVE_RESULT;
            }

        }

        // if the opponent has won ...
        else return NEGATIVE_RESULT;

    }

    // if the maximum tree depth is reached and the game is not over, continue checking other tree nodes
    if (tree_depth == LAST_TREE_LEVEL) return NEUTRAL_RESULT;

    // get one level deeper
    --tree_depth;

    // generate new movements for the next player
    return launch_board_generator(hexes, board, size, red_pawns_counter, blue_pawns_counter, number_of_hexes, tree_depth, main_player, perfect_opponent, number_of_moves, placed_red_pawns_counter, placed_blue_pawns_counter, alpha, beta);

}

// this function generates coordinates, boards, and checks a winner
bool launch_board_generator(stack* hexes, int** board, const int size, int* red_pawns_counter, int* blue_pawns_counter, int* number_of_hexes, int tree_depth, int main_player, bool perfect_opponent, int number_of_moves, int* placed_red_pawns_counter, int* placed_blue_pawns_counter, int alpha, int beta) {

    // create a stack consisting of all coordinates of empty hexes on the board
    auto* possible_movement_coordinates = create_possible_movement_coordinates(board, size);

    // calculate the amount of empty hexes (the ones without a pawn)
    // [ the variable defines how many possibilities there are on each level of the generated tree ]
    const int number_of_empty_hexes = *number_of_hexes - (*red_pawns_counter + *blue_pawns_counter);

    // get the current player (the one that should now place their pawn)
    bool current_player = determine_current_player(*red_pawns_counter, *blue_pawns_counter);

    // set the default result of the function
    int result = NEGATIVE_RESULT;

    // for each pair of possible coordinates ...
    for (int i = 0; i < number_of_empty_hexes; i++) {

        // get a pair of possible coords
        node* possible_movement_coordinates_pair = possible_movement_coordinates->pop();

        // place the current player's pawn onto a board on a generated position
        place_pawn(hexes, board, possible_movement_coordinates_pair, red_pawns_counter, blue_pawns_counter, current_player, placed_red_pawns_counter, placed_blue_pawns_counter);

        // check is there is a winning path
        result = minmax(hexes, board, size, red_pawns_counter, blue_pawns_counter, number_of_hexes, tree_depth, main_player, perfect_opponent, number_of_moves, placed_red_pawns_counter, placed_blue_pawns_counter, alpha, beta);

        // if there is a victory for the checked player ...
        if (result == POSITIVE_RESULT) {

            // clear the board back to the original state
            remove_pawn(hexes, board, possible_movement_coordinates_pair, red_pawns_counter, blue_pawns_counter, placed_red_pawns_counter, placed_blue_pawns_counter);

            possible_movement_coordinates->clear(); // free memory
            delete possible_movement_coordinates;
            delete possible_movement_coordinates_pair;

            return true; // immediately exit the function

        }

        // clear the board back to the original state
        remove_pawn(hexes, board, possible_movement_coordinates_pair, red_pawns_counter, blue_pawns_counter, placed_red_pawns_counter, placed_blue_pawns_counter);

        // free memory
        delete possible_movement_coordinates_pair;

        // if it's the main player's turn, update alpha
        if (check_maximizing(main_player, current_player)) alpha = max(alpha, NEGATIVE_RESULT);

        // if it's the opponent's turn, update beta
        else beta = min(beta, NEGATIVE_RESULT);

        // if the opponent won ...
        if (result == NEGATIVE_RESULT) {

            // apply alpha-beta pruning
            if (beta <= alpha) break;

        }

    }

    possible_movement_coordinates->clear(); // free memory
    delete possible_movement_coordinates;

    return false; // if nobody has won or the opponent player always has privilege, the checked player cannot win

}

bool check_can_player_win_in_n_moves(stack* hexes, int blue_pawns_counter, int red_pawns_counter, int number_of_hexes, int tree_depth, int main_player, int number_of_moves, bool perfect_opponent, bool print_the_result = false) {

    // if the board is not possible, immediately return from the function
    if (!check_is_board_possible(hexes, &blue_pawns_counter, &red_pawns_counter, &number_of_hexes)) {
        if (print_the_result) printf("NO\n");
        return false;
    }

    // if the board has instant win, there is nothing to check here, immediately return from the function
    bool winner;
    if (check_is_game_over(hexes, &blue_pawns_counter, &red_pawns_counter, &number_of_hexes, &winner)) {
        if (print_the_result) printf("NO\n");
        return false;
    }

    // get the size of the board
    const int size = get_board_size(number_of_hexes);

    // if the projected number of placed pawns of a player is way less than the minimal amount of pawns needed
    // to connect both sides of the board, immediately return from the function
    if ((main_player == red_pawn_symbol && red_pawns_counter + tree_depth < size) || (main_player == blue_pawn_symbol && blue_pawns_counter + tree_depth < size)) {
        if (print_the_result) printf("NO\n");
        return false;
    }

    // create an array representing the board
    int **board = create_board(hexes, size);

    // the tree depth has to be multiplied by two because there are *two* players placing the pawns
    // it represents the total number of moves needed to be made from both players
    tree_depth *= 2;

    // create added pawns counters for both players
    int placed_red_pawns_counter = 0, placed_blue_pawns_counter = 0;

    // create alpha and beta variables for the alpha-beta pruning
    int alpha = ABSOLUTE_ALPHA;
    int beta = ABSOLUTE_BETA;

    // check the possibility of winning for a desired player and store the result
    bool result = launch_board_generator(hexes, board, size, &red_pawns_counter, &blue_pawns_counter, &number_of_hexes, tree_depth, main_player, perfect_opponent, number_of_moves, &placed_red_pawns_counter, &placed_blue_pawns_counter, alpha, beta);

    // free memory
    free_array(board, size);

    if (result) {
        if (print_the_result) printf("YES\n");
        return true;
    }
    else {
        if (print_the_result) printf("NO\n");
        return false;
    }

}
