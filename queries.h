// this function will store and return a query
const char* get_query(int query_id) {

    switch (query_id) {
        case board_size: return "BOARD_SIZE";
        case pawns_number: return "PAWNS_NUMBER";
        case is_board_correct: return "IS_BOARD_CORRECT";
        case is_game_over: return "IS_GAME_OVER";
        case is_board_possible: return "IS_BOARD_POSSIBLE";
        case can_red_win_in_n_move_with_naive_opponent: return "CAN_RED_WIN_IN_N_MOVE_WITH_NAIVE_OPPONENT";
        case can_red_win_in_n_move_with_perfect_opponent: return "CAN_RED_WIN_IN_N_MOVE_WITH_PERFECT_OPPONENT";
        default: return "";
    }

}

// this function will retrieve the queries
const char** get_queries(const int number_of_queries) {

    // create an array of pointers to strings to store the queries' names
    const char** queries = new const char*[number_of_queries];

    // populate the array with the names of queries
    for (int i = 0; i < number_of_queries; i++) queries[i] = get_query(i);

    // return the queries array
    return queries;

}

// this function will update the function and symbol ID's based on the currently parsed symbol
bool compare_queries(int symbol, int* query_id, int* symbol_id) {

    // get the number of existent queries
    const int number_of_queries = queries_quantity;

    // retrieve the queries
    const char** queries = get_queries(number_of_queries);

    // iterate through the functions starting from the lastly valid function's ID
    for (int counter = *query_id; counter < number_of_queries; counter++) {

        // check if the content of the current node matches the current symbol
        if (symbol == queries[counter][*symbol_id]) {

            // update function_id to the current function
            *query_id = counter;

            // update symbol_id to the next symbol in the current function
            ++(*symbol_id);

            // if the next symbol is \n, the query is found
            if (*symbol_id == STRING_TERMINATOR) return true;

            // exit the function after updating identifiers
            return false;

        }

        // if there are difference in names, move to the next function, keeping what the program has already compared
        // i.e. without resetting 'symbol_id'
        else ++(*query_id);

    }

    return false;

}

// this function will create a dynamic array representing the game board
int** create_board(stack* hexes, const int size) {

    int** board = new int*[size];
    for (int i = 0; i < size; ++i) {
        board[i] = new int[size];
    }

    node* iterator = hexes->get_head();
    while (iterator != nullptr) {
        iterator = iterator->get_next();

        node* popped = hexes->pop();
        int x = popped->get_position_x();
        int y = popped->get_position_y();

        board[x][y] = popped->get_content();
        printf(">>> x: %d | y: %d <<<\n", x, y);

    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }

    hexes->clear();

    return board;

}

int get_board_size(int number_of_hexes) {
    return (int) sqrt(number_of_hexes);
}


void parse_query(stack* hexes, int symbol, int* query_id, int* symbol_id, const int* number_of_hexes, const int* red_pawns_counter, const int* blue_pawns_counter, bool* finished_board_parsing) {

    if (compare_queries(symbol, query_id, symbol_id)) {

        update_last_node_coords(hexes);

        *finished_board_parsing = true;

        switch (*query_id) {
            case board_size: {
                printf("%d\n", get_board_size(*number_of_hexes));
                break;
            }
            case pawns_number: {
                const int final_pawns_number = *red_pawns_counter + *blue_pawns_counter;
                printf("%d\n", final_pawns_number);
                break;
            }
            case is_board_correct: {
                (abs(*blue_pawns_counter - *red_pawns_counter) > PAWNS_MAX_DIFFERENCE) ? printf("NO\n") : printf("YES\n");
                break;
            }
            case is_game_over: {

                const int size = get_board_size(*number_of_hexes);

                // create an array representing the board
                int **board = create_board(hexes, size);

                // free memory
//                for (int i = 0; i < size; ++i) {
//                    delete[] board[i];
//                }
//                delete[] board;

                break;
            }
//                        case is_board_possible:
//                            break;
//                        case can_red_win_in_n_move_with_naive_opponent:
//                            break;
//                        case can_red_win_in_n_move_with_perfect_opponent:
//                            break;
            default:
                break;
        }

        *query_id = 0;
        *symbol_id = 0;

    }

}
