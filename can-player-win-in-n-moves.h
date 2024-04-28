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

// this function "virtually" places / removes the opponents pawn
// "virtually" because we are trying to generate as fewer iterations as possible
void update_opponent_data(int main_player, int* red_pawns_counter, int* blue_pawns_counter, bool mode = false) {

    // if the flag is set to false, the values will be incremented
    if (!mode) {
        if (main_player == red_pawn_symbol) ++(*blue_pawns_counter);
        else if (main_player == blue_pawn_symbol) ++(*red_pawns_counter);
    }

    // otherwise, decremented
    else {
        if (main_player == red_pawn_symbol) --(*blue_pawns_counter);
        else if (main_player == blue_pawn_symbol) --(*red_pawns_counter);
    }

}

// this function double-checks if the player used the correct amount of pawns to win the game
bool check_if_can_win_in_less_moves(stack* used_coords, int hexes[SIZE][SIZE], const int size, const int* blue_pawns_counter, const int* red_pawns_counter, const int* number_of_hexes) {

    // get the first pair of used coordinates
    node* iterator = used_coords->get_head();

    while (iterator != nullptr) {

        // iterate through the game board ...
        for (int k = 0; k < size; k++) {
            for (int l = 0; l < size; l++) {

                // if the hex with the specified coords is found ...
                if (k == iterator->get_position_x() && l == iterator->get_position_y()) {

                    // save its content
                    int content = hexes[k][l];

                    // make this hex empty
                    hexes[k][l] = empty_hex_symbol;

                    bool winner;

                    // if the player can still win even without one of their hexes, it means that there is
                    // an "overflow" of moves, e.g. 1 move wanted, 2 made
                    if (check_is_game_over(hexes, blue_pawns_counter, red_pawns_counter, number_of_hexes, &winner)) return false;

                    // otherwise, restore the hex and continue the check
                    hexes[k][l] = content;

                }
            }
        }

        iterator = iterator->get_next();
    }

    return true;

}

// this function searches for free hexes and saves their coordinates onto the stack
auto* create_possible_movement_coordinates(int hexes[SIZE][SIZE], const int size) {

    // create a new stack
    auto* possible_movement_coordinates = new stack();

    // iterate through the stack
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            // if the hex is empty (neither red, nor blue) ...
            if (hexes[i][j] != red_pawn_symbol && hexes[i][j] != blue_pawn_symbol) {

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
void place_pawn(int hexes[SIZE][SIZE], node* possible_movement_coordinates_pair, int* red_pawns_counter, int* blue_pawns_counter, int current_player) {

    // get the coords
    int x = possible_movement_coordinates_pair->get_position_x();
    int y = possible_movement_coordinates_pair->get_position_y();

    // create a variable that stores the pawn's ascii
    int pawn = UNDEFINED;

    // if the current player is red [ true ], the pawn is red
    if (current_player == red_pawn_symbol) {
        ++(*red_pawns_counter);
        pawn = red_pawn_symbol;
    }

    // otherwise the pawn is blue
    else if (current_player == blue_pawn_symbol){
        ++(*blue_pawns_counter);
        pawn = blue_pawn_symbol;
    }

    // place the pawn onto the board
    hexes[x][y] = pawn;

}

// this function removes an added pawn from the board
void remove_pawn(int hexes[SIZE][SIZE], node* possible_movement_coordinates_pair, int* red_pawns_counter, int* blue_pawns_counter) {

    // get the coords
    int x = possible_movement_coordinates_pair->get_position_x();
    int y = possible_movement_coordinates_pair->get_position_y();

    if (hexes[x][y] == red_pawn_symbol) --(*red_pawns_counter);
    else if (hexes[x][y] == blue_pawn_symbol) --(*blue_pawns_counter);

    // replace the pawn with a dot [ empty ]
    hexes[x][y] = empty_hex_symbol;

}

// this function generates possible moves, places pawns and checks for a player's victory
bool bruteforce_traverse(int hexes[SIZE][SIZE], const int size, int* number_of_hexes, int* red_pawns_counter, int* blue_pawns_counter, int tree_depth, int main_player, int number_of_empty_hexes, stack* used_coords) {

    // create a stack consisting of all coordinates of empty hexes on the board
    auto* possible_movement_coordinates = create_possible_movement_coordinates(hexes, size);

    // iterate through all possibilities
    for (int i = 0; i < number_of_empty_hexes; i++) {

        // get a pair of possible coords
        node* possible_movement_coordinates_pair = possible_movement_coordinates->pop();

        // push the pair to the stack to keep track of what coords were used in case of victory
        used_coords->push(UNDEFINED, possible_movement_coordinates_pair->get_position_x(), possible_movement_coordinates_pair->get_position_y());

        // place the current player's pawn onto a board on a generated position
        place_pawn(hexes, possible_movement_coordinates_pair, red_pawns_counter, blue_pawns_counter, main_player);

        // if there is only one move to be made by a player ...
        if (tree_depth == MINIMAL_TREE_DEPTH) {

            bool winner;

            // if the pawn placement make it possible for a player to win ...
            if (check_is_game_over(hexes, blue_pawns_counter, red_pawns_counter, number_of_hexes, &winner, false)) {

                // if the player, for whom the traverse is being made, is the one winning ...
                if ((main_player == red_pawn_symbol && winner) || (main_player == blue_pawn_symbol && !winner)) {

                    // clear the board back to the original state by removing a placed pawn
                    remove_pawn(hexes, possible_movement_coordinates_pair, red_pawns_counter, blue_pawns_counter);

                    delete possible_movement_coordinates_pair; // free memory
                    possible_movement_coordinates->clear();
                    delete possible_movement_coordinates;

                    // double-check if the amount of pawns used is correct
                    bool pawns_check = check_if_can_win_in_less_moves(used_coords, hexes, size, blue_pawns_counter, red_pawns_counter, number_of_hexes);

                    if (!pawns_check) return false; // the player used too many pawns, cannot win in n-moves

                    return true; // the checked player can win in n-moves

                }

            }

            // if nobody has won ...
            else {

                // clear the board back to the original state by removing a placed pawn
                remove_pawn(hexes, possible_movement_coordinates_pair, red_pawns_counter, blue_pawns_counter);

                delete used_coords->pop(); // remove the saved coord since they aren't the ones giving the player victory
                delete possible_movement_coordinates_pair; // free memory

            }

        }

        // if there are more moves to be made by a player ...
        else {

            // the opponent now has to "virtually" place their pawn
            update_opponent_data(main_player, red_pawns_counter, blue_pawns_counter);

            // the actual player has to place another pawn and check for victory
            // if the player wins ...
            if (bruteforce_traverse(hexes, size, number_of_hexes, red_pawns_counter, blue_pawns_counter, tree_depth - 1, main_player, number_of_empty_hexes - 1, used_coords)) {

                // remove the "virtual" pawn of the opponent
                update_opponent_data(main_player, red_pawns_counter, blue_pawns_counter, true);

                // clear the board back to the original state by removing a placed pawn
                remove_pawn(hexes, possible_movement_coordinates_pair, red_pawns_counter, blue_pawns_counter);

                delete used_coords->pop(); // remove the saved coord since they aren't the ones giving the player victory
                delete possible_movement_coordinates_pair; // free memory
                possible_movement_coordinates->clear();
                delete possible_movement_coordinates;

                return true; // the checked player can win in n-moves

            }

            // clear the board back to the original state by removing a placed pawn
            remove_pawn(hexes, possible_movement_coordinates_pair, red_pawns_counter, blue_pawns_counter);

            delete used_coords->pop(); // remove the saved coord since they aren't the ones giving the player victory

            // remove the "virtual" pawn of the opponent
            update_opponent_data(main_player, red_pawns_counter, blue_pawns_counter, true);

        }

    }

    possible_movement_coordinates->clear(); // free memory
    delete possible_movement_coordinates;

    return false; // the player hasn't won

}

// this function checks base cases before launching moves generator and returns result of a request
bool check_can_player_win_in_n_moves(int hexes[SIZE][SIZE], int blue_pawns_counter, int red_pawns_counter, int number_of_hexes, int tree_depth, int main_player, bool print_the_result = false) {

    // get the size of the board
    const int size = get_board_size(number_of_hexes);

    // if the board has instant win, there is nothing to check here, immediately return from the function
    bool winner;
    if (check_is_game_over(hexes, &blue_pawns_counter, &red_pawns_counter, &number_of_hexes, &winner)) {
        if (print_the_result) printf("NO\n");
        return false;
    }

    // if the board is not possible, immediately return from the function
    if (!check_is_board_possible(hexes, &blue_pawns_counter, &red_pawns_counter, &number_of_hexes)) {
        if (print_the_result) printf("NO\n");
        return false;
    }

    // if the projected number of placed pawns of a player is way less than the minimal amount of pawns needed
    // to connect both sides of the board, immediately return from the function
    if ((main_player == red_pawn_symbol && red_pawns_counter + tree_depth < size) || (main_player == blue_pawn_symbol && blue_pawns_counter + tree_depth < size)) {
        if (print_the_result) printf("NO\n");
        return false;
    }

    // calculate the amount of empty hexes (the ones without a pawn)
    // [ the variable defines how many possibilities there are on each level of the generated tree ]
    const int number_of_empty_hexes = number_of_hexes - (red_pawns_counter + blue_pawns_counter);

    // determine the number of total moves needed to be made by both players
    // if the program looks for the max result (i.e. checked player != current player), there are 4 moves, otherwise, 3
    int total_moves;
    (check_maximizing(main_player, determine_current_player(red_pawns_counter, blue_pawns_counter))) ? total_moves = maximizing_case_total_moves : total_moves = minimizing_case_total_moves;

    // if the player has only one move to make, decrement the total moves by 2
    if (tree_depth == MINIMAL_TREE_DEPTH) total_moves -= one_move_total_moves_factor;

    // if there are more moves required to be made than empty hexes where the pawns can be put, the player cannot win
    // in the specified amount of moves, immediately return from the program
    if (total_moves > number_of_empty_hexes) {
        if (print_the_result) printf("NO\n");
        return false;
    }

    // create a stack to store all the put hexes' coords
    auto* used_coords = new stack;

    // create a variable to store the result of the function
    bool result;

    // if the program looks for the max result (i.e. checked player != current player) ...
    if (check_maximizing(main_player, determine_current_player(red_pawns_counter, blue_pawns_counter))) {

        // the opponent has to make a move first
        update_opponent_data(main_player, &red_pawns_counter, &blue_pawns_counter);

    }

    // launch bruteforce i.e. check if the player can win in n-moves
    result = bruteforce_traverse(hexes, size, &number_of_hexes, &red_pawns_counter, &blue_pawns_counter, tree_depth, main_player, number_of_empty_hexes, used_coords);

    used_coords->clear(); // free memory
    delete used_coords;

    if (result) {
        if (print_the_result) printf("YES\n");
        return true;
    }
    else {
        if (print_the_result) printf("NO\n");
        return false;
    }

}
