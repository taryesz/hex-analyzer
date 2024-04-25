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

bool check_maximizing(int main_player, int current_player) {

    if (main_player == blue_pawn_symbol) {
        if (current_player) return true;  // max
        else return false;                // min
    }
    else {
        if (current_player) return false; // min
        else return true;                 // max
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

bool launch_board_generator(stack* hexes, int** board, int size, int* red_pawns_counter, int* blue_pawns_counter, int* number_of_hexes, int tree_depth, int main_player, bool perfect_opponent, int number_of_moves, int* placed_red_pawns_counter, int* placed_blue_pawns_counter, int alpha, int beta);

int minmax(stack* hexes, int** board, const int size, int* red_pawns_counter, int* blue_pawns_counter, int* number_of_hexes, int tree_depth, int main_player, bool perfect_opponent, int number_of_moves, int* placed_red_pawns_counter, int* placed_blue_pawns_counter, int alpha, int beta) {

    bool winner;

    // check if the game is over and if so, return true
    if (check_is_game_over(hexes, blue_pawns_counter, red_pawns_counter, number_of_hexes, &winner, false)) {
        if ((main_player == red_pawn_symbol && winner) || (main_player == blue_pawn_symbol && !winner)) {

            if (main_player == red_pawn_symbol) {
                if (*placed_red_pawns_counter < number_of_moves) {
//                    printf(">>> CHECK IF MORE PAWNS CAN BE PLACED\n\n");
                }
                else {
//                    printf(">>> GAME OVER - RED WON\n\n");
                    return POSITIVE_RESULT;
                }
            }
            else {
                if (*placed_blue_pawns_counter < number_of_moves) {
//                    printf(">>> CHECK IF MORE PAWNS CAN BE PLACED\n\n");
                }
                else {
//                    printf(">>> GAME OVER - BLUE WON\n\n");
                    return POSITIVE_RESULT;
                }
            }

        }
        else {
//            printf(">>> GAME OVER - WE LOST\n\n");
            return NEGATIVE_RESULT;
        }
    }

    // if the maximum tree depth is reached and the game is not over, return false
    if (tree_depth == LAST_TREE_LEVEL) {
//        printf(">>> MAX LEVEL REACHED\n\n");
        return NEUTRAL_RESULT;
    }

    --tree_depth;

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

    int result = false;

    // for each pair of possible coordinates ...
    for (int i = 0; i < number_of_empty_hexes; i++) {

        // get a pair of possible coords
        node* possible_movement_coordinates_pair = possible_movement_coordinates->pop();

        // place the current player's pawn onto a board on a generated position
        place_pawn(hexes, board, possible_movement_coordinates_pair, red_pawns_counter, blue_pawns_counter, current_player, placed_red_pawns_counter, placed_blue_pawns_counter);

//        printf("THE NEW BOARD: \n\n");
//        print_array(board, size);
//        printf("------------------------------- \n\n");

        // check is there is a winning path
        result = minmax(hexes, board, size, red_pawns_counter, blue_pawns_counter, number_of_hexes, tree_depth, main_player, perfect_opponent, number_of_moves, placed_red_pawns_counter, placed_blue_pawns_counter, alpha, beta);

        if (result == POSITIVE_RESULT) {

            // clear the board back to the original state
            remove_pawn(hexes, board, possible_movement_coordinates_pair, red_pawns_counter, blue_pawns_counter, placed_red_pawns_counter, placed_blue_pawns_counter);

            possible_movement_coordinates->clear();
            delete possible_movement_coordinates;

            // free memory
            delete possible_movement_coordinates_pair;

            return true;

        }

        // clear the board back to the original state
        remove_pawn(hexes, board, possible_movement_coordinates_pair, red_pawns_counter, blue_pawns_counter, placed_red_pawns_counter, placed_blue_pawns_counter);

        // free memory
        delete possible_movement_coordinates_pair;

        // If it's main player's turn, update alpha
        if (check_maximizing(main_player, current_player)) {
            alpha = max(alpha, NEGATIVE_RESULT);
        }

        // If it's opponent's turn, update beta
        else {
            beta = min(beta, NEGATIVE_RESULT);
        }

        // if neutral result <=> out of moves
        if (result == NEGATIVE_RESULT) {

            // Apply alpha-beta pruning
            if (beta <= alpha) {
                // printf("PRUNED\n");
                break;
            }

        }

    }

    possible_movement_coordinates->clear();
    delete possible_movement_coordinates;

    if (result == NEUTRAL_RESULT) return false;

    return result;

}

bool check_can_player_win_in_n_moves(stack* hexes, int blue_pawns_counter, int red_pawns_counter, int number_of_hexes, int tree_depth, int main_player, int number_of_moves, bool perfect_opponent, bool print_the_result = false) {

    // if the board is not possible, immediately return from the function
    if (!check_is_board_possible(hexes, &blue_pawns_counter, &red_pawns_counter, &number_of_hexes)) {
        if (print_the_result) printf("NO\n");
        return false;
    }

    bool winner;
    if (check_is_game_over(hexes, &blue_pawns_counter, &red_pawns_counter, &number_of_hexes, &winner)) {
        if (print_the_result) printf("NO\n");
        return false;
    }

    // get the size of the board
    const int size = get_board_size(number_of_hexes);

    if ((main_player == red_pawn_symbol && red_pawns_counter + tree_depth < size) || (main_player == blue_pawn_symbol && blue_pawns_counter + tree_depth < size)) {
        if (print_the_result) printf("NO\n");
        return false;
    }

    // create an array representing the board
    int **board = create_board(hexes, size);

    const int number_of_empty_hexes = number_of_hexes - (red_pawns_counter + blue_pawns_counter);

    // create a stack consisting of all coordinates of empty hexes on the board
    auto* possible_movement_coordinates = create_possible_movement_coordinates(board, size);

    // get the current player (the one that should now place their pawn)
    bool current_player = determine_current_player(red_pawns_counter, blue_pawns_counter);

    int placed_red_pawns_counter = 0, placed_blue_pawns_counter = 0;

    int movements = 3; // RR or BB
    if (check_maximizing(main_player, current_player)) movements = 4; // RB or BR

    if (tree_depth == 1) movements -= 2; // for one step

    node* possible_movement_coordinates_pair = possible_movement_coordinates->get_head();
    node* possible_movement_coordinates_pair2 = possible_movement_coordinates->get_head();

    // current_player = (main_player == red_pawn_symbol);

    if (movements <= number_of_empty_hexes) {

        for (int i = 0; i < number_of_empty_hexes; i++) {

            place_pawn(hexes, board, possible_movement_coordinates_pair, &red_pawns_counter, &blue_pawns_counter, current_player, &placed_red_pawns_counter, &placed_blue_pawns_counter);

            if (check_maximizing(main_player, current_player)) {

                current_player = determine_current_player(red_pawns_counter, blue_pawns_counter);

                for (int j = 0; j < number_of_empty_hexes - 1; j++) {

                    if (possible_movement_coordinates_pair->get_position_x() == possible_movement_coordinates_pair2->get_position_x() && possible_movement_coordinates_pair->get_position_y() == possible_movement_coordinates_pair2->get_position_y()) {
                        if (possible_movement_coordinates_pair2->get_next() != nullptr) possible_movement_coordinates_pair2 = possible_movement_coordinates_pair2->get_next();
                    }

                    place_pawn(hexes, board, possible_movement_coordinates_pair2, &red_pawns_counter, &blue_pawns_counter, current_player, &placed_red_pawns_counter, &placed_blue_pawns_counter);

                    if (check_is_game_over(hexes, &blue_pawns_counter, &red_pawns_counter, &number_of_hexes, &winner)) {
                        // main won:
                        if ((winner && main_player == red_pawn_symbol) || (!winner && main_player == blue_pawn_symbol)) {
                            if (print_the_result) printf("YES\n");
                            remove_pawn(hexes, board, possible_movement_coordinates_pair, &red_pawns_counter, &blue_pawns_counter, &placed_red_pawns_counter, &placed_blue_pawns_counter);
                            remove_pawn(hexes, board, possible_movement_coordinates_pair2, &red_pawns_counter, &blue_pawns_counter, &placed_red_pawns_counter, &placed_blue_pawns_counter);
                            possible_movement_coordinates->clear();
                            delete possible_movement_coordinates;
                            free_array(board, size);
                            return true;
                        }
                        // opponent won ...
                    }

                    remove_pawn(hexes, board, possible_movement_coordinates_pair2, &red_pawns_counter, &blue_pawns_counter, &placed_red_pawns_counter, &placed_blue_pawns_counter);
                    if (possible_movement_coordinates_pair2->get_next() != nullptr) possible_movement_coordinates_pair2 = possible_movement_coordinates_pair2->get_next();

                }

                remove_pawn(hexes, board, possible_movement_coordinates_pair, &red_pawns_counter, &blue_pawns_counter, &placed_red_pawns_counter, &placed_blue_pawns_counter);
                current_player = determine_current_player(red_pawns_counter, blue_pawns_counter);
                continue;

            }
            else {

                if (check_is_game_over(hexes, &blue_pawns_counter, &red_pawns_counter, &number_of_hexes, &winner)) {
                    // main won:
                    if ((winner && main_player == red_pawn_symbol) || (!winner && main_player == blue_pawn_symbol)) {
                        if (print_the_result) printf("YES\n");
                        remove_pawn(hexes, board, possible_movement_coordinates_pair, &red_pawns_counter, &blue_pawns_counter, &placed_red_pawns_counter, &placed_blue_pawns_counter);
                        possible_movement_coordinates->clear();
                        delete possible_movement_coordinates;
                        free_array(board, size);
                        return true;
                    }
                    // opponent won ...
                }

                remove_pawn(hexes, board, possible_movement_coordinates_pair, &red_pawns_counter, &blue_pawns_counter, &placed_red_pawns_counter, &placed_blue_pawns_counter);
                if (possible_movement_coordinates_pair->get_next() != nullptr) possible_movement_coordinates_pair = possible_movement_coordinates_pair->get_next();

            }

            // place_pawn(current)

            // if maximizing == true:                               ::::*** if RB or BR ***::::
            //      update_current_player()                         RB -> blue moves = red moves = 1
            //      for number_of_empty_hexes - 1 :                 BR -> blue moves = red moves = 1
            //          place_pawn(current)                         Total moves = 2
            //          is_game_over() ? return true
            //          remove_pawn(current)
            //          get_next_possible_coord_2()
            //      remove_pawn(current)
            //      update_current_player()
            //      continue
            //
            // else:                                                 ::::*** if RR or BB ***::::
            //      is_game_over() ? return true                     RR -> blue moves = 0, red moves = 1
            //      remove_pawn(current)                             BB -> blue moves = 1, red moves = 0
            //      get_next_possible_coord()                        Total moves = 1

        }

    }

    // REMOVE PAWN

    // printf(">>> pawns counter test: red = %d, blue = %d\n", red_pawns_counter, blue_pawns_counter);

    possible_movement_coordinates->clear();
    delete possible_movement_coordinates;

    free_array(board, size);

    if (print_the_result) printf("NO\n");
    return false;

}