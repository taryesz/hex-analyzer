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

        // iterate through the symbols of the current function
        for (int symbol_counter = *symbol_id; queries[counter][symbol_counter] != STRING_TERMINATOR; symbol_counter++) {

            // check if the content of the current node matches the current symbol
            if (symbol == queries[counter][symbol_counter]) {

                // update function_id to the current function
                *query_id = counter;

                // update symbol_id to the next symbol in the current function
                *symbol_id = ++symbol_counter;

                // if the next symbol is \n, the query is found
                if (*symbol_id == STRING_TERMINATOR) return true;

                // exit the function after updating identifiers
                return false;

            }
            else {
                *symbol_id = 0;
                break;
            }

        }

    }

    return false;

}
