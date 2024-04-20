float max(float a, float b) {
    if (a > b) return a;
    else if (b > a) return b;
    else return a;
}

float min(float a, float b) {
    if (a < b) return a;
    else if (b < a) return b;
    else return a;
}

auto* create_possible_movement_coordinates(int** board, const int size) {

    auto* possible_movement_coordinates = new stack();

    // find the empty spaces and save their coords on stack
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] != red_pawn_symbol && board[i][j] != blue_pawn_symbol) {
                // save the coords of an empty space
                possible_movement_coordinates->push(UNDEFINED, i, j);
            }
        }
    }

    return possible_movement_coordinates;

}

int** create_possible_movement_board(stack* hexes, node* popped, const int size, int current_player, int** board) {

    int** possible_movement_board = copy_array(board, size);
    possible_movement_board[popped->get_position_x()][popped->get_position_y()] = current_player;

    node* iterator = hexes->get_head();
    while (iterator != nullptr) {
        if (iterator->get_position_x() == popped->get_position_x() && iterator->get_position_y() == popped->get_position_y()) {
            iterator->set_content(current_player);
        }
        iterator = iterator->get_next();
    }

    hexes->print();
    printf(">>> generating one of the possible board scenarios ... \n\n");
    print_array(possible_movement_board, size);
    printf(">>> end generating \n\n");

    return possible_movement_board;

}

bool check_min_or_max_tree(int player, int current_player) {

    if (player == blue_pawn_symbol && current_player == blue_pawn_symbol) return false; // min
    if (player == blue_pawn_symbol && current_player == red_pawn_symbol) return true; // max
    if (player == red_pawn_symbol && current_player == blue_pawn_symbol) return true; // max
    if (player == red_pawn_symbol && current_player == red_pawn_symbol) return false; // min

    return true;

}

bool minmax(stack* hexes, int** board, float* alpha, float* beta, const int size, int blue_pawns_counter, int red_pawns_counter, int number_of_hexes, int number_of_empty_hexes, int generated_possibilities_tree_depth, int player, int current_player) {

    // if the maximum level of depth reached, check if the game over and return true or false accordingly
    bool result = check_is_game_over(hexes, &blue_pawns_counter, &red_pawns_counter, &number_of_hexes);

    if (result) return true;

    if (generated_possibilities_tree_depth == 0) return false;

    --number_of_empty_hexes;

    player = current_player;
    if (current_player == red_pawn_symbol) current_player = blue_pawn_symbol;
    else if (current_player == blue_pawn_symbol) current_player = red_pawn_symbol;

    auto* possible_movement_coordinates = create_possible_movement_coordinates(board, size);

    if (check_min_or_max_tree(player, current_player)) {
        float best_local_result = -INFINITY;
        for (int i = 0; i < number_of_empty_hexes; i++) {

            int x = possible_movement_coordinates->get_head()->get_position_x();
            int y = possible_movement_coordinates->get_head()->get_position_y();

            node* popped = possible_movement_coordinates->pop();

            int** possible_movement_board = create_possible_movement_board(hexes, popped, size, current_player, board);

            delete popped;

            float local_result = minmax(hexes, possible_movement_board, alpha, beta, size, blue_pawns_counter, red_pawns_counter, number_of_hexes, number_of_empty_hexes, generated_possibilities_tree_depth - 1, player, current_player);

            node* iterator = hexes->get_head();
            while (iterator != nullptr) {
                if (iterator->get_position_x() == x && iterator->get_position_y() == y) {
                    iterator->set_content(default_symbol);
                    break;
                }
                iterator = iterator->get_next();
            }

            best_local_result = max(best_local_result, local_result);
            *alpha = max(*alpha, best_local_result);
            if (*alpha >= *beta) break;
        }
        return best_local_result;
    }
    else {
        float best_local_result = INFINITY;
        for (int i = 0; i < number_of_empty_hexes; i++) {

            int x = possible_movement_coordinates->get_head()->get_position_x();
            int y = possible_movement_coordinates->get_head()->get_position_y();

            node* popped = possible_movement_coordinates->pop();

            int **possible_movement_board = create_possible_movement_board(hexes, popped, size, current_player, board);

            delete popped;

            float local_result = minmax(hexes, possible_movement_board, alpha, beta, size, blue_pawns_counter, red_pawns_counter, number_of_hexes, number_of_empty_hexes, generated_possibilities_tree_depth - 1, player, current_player);

            node* iterator = hexes->get_head();
            while (iterator != nullptr) {
                if (iterator->get_position_x() == x && iterator->get_position_y() == y) {
                    iterator->set_content(default_symbol);
                    break;
                }
                iterator = iterator->get_next();
            }

            best_local_result = min(best_local_result, local_result);
            *beta = min(*beta, best_local_result);
            if (*alpha >= *beta) break;
        }
        return best_local_result;
    }

}

// TODO: THIS IS A NAIVE IMPLEMENTATION? CRASHES - FIX IT.
bool check_can_player_win_in_n_moves(stack* hexes, const int* blue_pawns_counter, const int* red_pawns_counter, const int* number_of_hexes, int player, int number_of_moves, bool print_the_result = false) {

    if (!check_is_board_possible(hexes, blue_pawns_counter, red_pawns_counter, number_of_hexes) ||
        check_is_game_over(hexes, blue_pawns_counter, red_pawns_counter, number_of_hexes)) {
        if (print_the_result) printf("NO\n");
        return false;
    }

    int current_player = red_pawn_symbol;
    if (*red_pawns_counter > *blue_pawns_counter) current_player = blue_pawn_symbol; // blue's turn

    float best_local_result;
    (check_min_or_max_tree(player, current_player)) ? best_local_result = -INFINITY : best_local_result = INFINITY;

    float alpha = -INFINITY;
    float beta = INFINITY;

    // get the size of the board
    const int size = get_board_size(*number_of_hexes);

    // create an array representing the board
    int **board = create_board(hexes, size);

    // calculate the amount of empty hexes (the ones without a pawn)
    const int number_of_empty_hexes = *number_of_hexes - (*red_pawns_counter + *blue_pawns_counter);

    // create a stack consisting of all coordinates of empty hexes on the board
    auto* possible_movement_coordinates = create_possible_movement_coordinates(board, size);

    int move;

    int generated_possibilities_tree_depth = 2 * number_of_moves;

    // for each pair of possible coordinates ...
    for (int i = 0; i < number_of_empty_hexes; i++) {

        node* popped = possible_movement_coordinates->pop();

        int** possible_movement_board = create_possible_movement_board(hexes, popped, size, current_player, board);

//        player = current_player;
//        if (current_player == red_pawn_symbol) current_player = blue_pawn_symbol;
//        else if (current_player == blue_pawn_symbol) current_player = red_pawn_symbol; // TODO: always true

        float local_result = minmax(hexes, possible_movement_board, &alpha, &beta, size, *blue_pawns_counter, *red_pawns_counter, *number_of_hexes, number_of_empty_hexes, generated_possibilities_tree_depth - 1, player, current_player);

        if (check_min_or_max_tree(player, current_player) && (local_result >= best_local_result)) {
            best_local_result = local_result;
            alpha = max(alpha, best_local_result);
            move = i;
        }
        else if (!check_min_or_max_tree(player, current_player) && (local_result < best_local_result)) {
            best_local_result = local_result;
            beta = min(beta, best_local_result);
            move = i;
        }

        hexes->replace(popped, default_symbol);
        delete popped;

        // todo: clear the added possibility (root) pawn for the next generation (how?)

//        if (current_player == red_pawn_symbol) current_player = blue_pawn_symbol;
//        else if (current_player == blue_pawn_symbol) current_player = red_pawn_symbol; // TODO: ????????

    }

    if (print_the_result) printf("%d\n", move);
    return (bool) move;

}
