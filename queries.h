#include "array.h"

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
            if (*symbol_id == STRING_TERMINATOR) {
                delete [] queries; // free memory
                return true;

            }

            // exit the function after updating identifiers
            delete [] queries; // free memory
            return false;


        }

            // if there are difference in names, move to the next function, keeping what the program has already compared
            // i.e. without resetting 'symbol_id'
        else ++(*query_id);


    }

    delete [] queries; // free memory
    return false;

}

// this function will create a dynamic array representing the game board
int** create_board(stack* hexes, const int size) {

    // create a dynamic size x size 2D-array of integers
    int** board = create_array<int>(size);

    // get the head of the stack
    node* iterator = hexes->get_head();

    // while there are elements on the stack
    while (iterator != nullptr) {

        // get the next element
        iterator = iterator->get_next();

        // remove the current element from the stack
        node* popped = hexes->pop();

        // get the popped's coords
        int x = popped->get_position_x();
        int y = popped->get_position_y();

        // place the popped's pawn value into the respective spot in the array
        board[x][y] = popped->get_content();

        delete popped; // free memory

    }

    // get rid of the stack since the program doesn't need it anymore:
    // all pawns and hexes were transferred into the dynamic array
    hexes->clear();

    // return the filled out board
    return board;

}

// this function returns the counted board size
int get_board_size(int number_of_hexes) {
    return (int) sqrt(number_of_hexes); // the board is always of size AxA, so just get the root
}

// this function looks for connections between board edges
bool traverse_board(int** board, bool** visited, int x, int y, int size, int current_player, int opposite_player) {

    // if the symbol that is being currently checked either doesn't exist because of non-existent coordinates
    // or the symbol was already visited (i.e. taken into account earlier), or the symbol is a pawn of the opposite player,
    // ignore this symbol
    if (x < 0 || x >= size || y < 0 || y >= size || visited[x][y] || board[x][y] != current_player) return false;

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
    return (traverse_board(board, visited, x, y - 1, size, current_player, opposite_player) ||
            traverse_board(board, visited, x, y + 1, size, current_player, opposite_player) ||
            traverse_board(board, visited, x + 1, y, size, current_player, opposite_player) ||
            traverse_board(board, visited, x - 1, y, size, current_player, opposite_player) ||
            traverse_board(board, visited, x + 1, y + 1, size, current_player, opposite_player) ||
            traverse_board(board, visited, x - 1, y - 1, size, current_player, opposite_player));

}

// this function executes IS_GAME_OVER query, i.e. checks if one of the player has connected their edges with pawns
bool check_is_game_over(int** board, const int size, bool* winner, bool** visited_blue, bool** visited_red) {

    // create a variable that will store the permanent index of an element
    // *** along the edge of the board ***
    // [ blue player --- left & right edge, so 0 will be set for Y-axis ]
    // [ red player  --- top & bottom edge, so 0 will be set for X-axis ]
    // *** the axes are mirrored because the array is too ***
    const int edge_symbol_mark = 0;

    // launch the board traversal looking for 'r' connecting the opposite board's sides
    for (int i = 0; i < size; i++) {

        // if an 'r' was found along the edge and the connection to the opposite edge is found too ...
        if (board[edge_symbol_mark][i] == red_pawn_symbol && traverse_board(board, visited_red, edge_symbol_mark, i, size, red_pawn_symbol, blue_pawn_symbol)) {

            // the red player becomes the winner [ true ]
            *winner = true;

            // IS_GAME_OVER confirms to be over
            return true;

        }

    }

    // launch the board traversal looking for 'b' connecting the opposite board's sides
    for (int i = 0; i < size; i++) {

        // if an 'b' was found along the edge and the connection to the opposite edge is found too ...
        if (board[i][edge_symbol_mark] == blue_pawn_symbol && traverse_board(board, visited_blue, i, edge_symbol_mark, size, blue_pawn_symbol, red_pawn_symbol)) {

            // the blue player becomes the winner [ false ]
            *winner = false;

            // IS_GAME_OVER confirms to be over
            return true;

        }

    }

    // IS_GAME_OVER is not over, no connections found
    return false;

}

// this function checks if the amount of blue and red pawns is possible
bool check_is_board_correct(int blue_pawns_counter, int red_pawns_counter, int number_of_hexes) {

    // if there are more blues than reds, it's not possible so false
    if (blue_pawns_counter > red_pawns_counter) return false;

    // if there is only one hex on the board, and it's a blue one, can't be because the game starts the red one
    else if (number_of_hexes == 1 && (!red_pawns_counter && blue_pawns_counter)) return false;

    // if there is only one hex on the board, and it's a red one, it's a possible scenario
    else if (number_of_hexes == 1 && (!blue_pawns_counter && red_pawns_counter)) return true;

    // if none of the above ...
    else {

        // if the difference in the amount of blue and red pawns is greater than one, can't be
        if (abs(blue_pawns_counter - red_pawns_counter) > PAWNS_MAX_DIFFERENCE) return false;

        // otherwise, everything's fine
        else return true;

    }

}

// this function compares the input letters with the defined queries and executes one when detected
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
                if (check_is_board_correct(*blue_pawns_counter, *red_pawns_counter, *number_of_hexes)) printf("YES\n");
                else printf("NO\n");
                break;
            }
            case is_game_over: {

                if (!check_is_board_correct(*blue_pawns_counter, *red_pawns_counter, *number_of_hexes)) {
                    printf("NO\n");
                    break;
                }

                const int size = get_board_size(*number_of_hexes);

                // create an array representing the board
                int **board = create_board(hexes, size);
                bool winner;

                // create a dynamic size x size 2D-array of false's to keep track of visited elements
                bool** visited_blue = create_array<bool>(size, true, false);
                bool** visited_red = create_array<bool>(size, true, false);

                if (check_is_game_over(board, size, &winner, visited_blue, visited_red)) {
                    printf("YES ");
                    (winner) ? printf("RED\n") : printf("BLUE\n");

                } else printf("NO\n");

                // free memory
                free_array(board, size);
                free_array(visited_blue, size);
                free_array(visited_red, size);
                break;

            }
            case is_board_possible: {

                if (!check_is_board_correct(*blue_pawns_counter, *red_pawns_counter, *number_of_hexes)) {
                    printf("NO\n");
                    break;
                }

                const int size = get_board_size(*number_of_hexes);

                // create an array representing the board
                int **board = create_board(hexes, size);
                bool winner;
                bool is_board_possible = false;

                // create a dynamic size x size 2D-array of false's to keep track of visited elements
                bool** visited_blue = create_array<bool>(size, true, false);
                bool** visited_red = create_array<bool>(size, true, false);

                // needed to initiate the "winner" variable
                bool is_game_over = check_is_game_over(board, size, &winner, visited_blue, visited_red);

                if (size != 2) {

                    if (is_game_over) {

                        if (winner) {

                            for (int i = 0; i < size; i++) {
                                for (int j = 0; j < size; j++) {
                                    if (visited_red[i][j]) {
                                        board[i][j] = default_symbol;
                                        bool **visited_blue_copy = create_array<bool>(size, true, false);
                                        bool **visited_red_copy = create_array<bool>(size, true, false);

                                        if (!check_is_game_over(board, size, &winner, visited_blue_copy,visited_red_copy)) {
                                            is_board_possible = true;
                                            i = size;
                                            break;
                                        }
                                        else {
                                            if (is_board_possible) {
                                                is_board_possible = false;
                                                free_array(visited_blue_copy, size);
                                                free_array(visited_red_copy, size);
                                                i = size;
                                                break;
                                            }
                                            board[i][j] = red_pawn_symbol;
                                        }

                                        free_array(visited_blue_copy, size);
                                        free_array(visited_red_copy, size);
                                    }
                                }
                            }

                            if (*red_pawns_counter <= *blue_pawns_counter) is_board_possible = false;

                        }
                        else {

                            for (int i = 0; i < size; i++) {
                                for (int j = 0; j < size; j++) {
                                    if (visited_blue[i][j]) {
                                        board[i][j] = default_symbol;
                                        bool **visited_blue_copy = create_array<bool>(size, true, false);
                                        bool **visited_red_copy = create_array<bool>(size, true, false);

                                        if (!check_is_game_over(board, size, &winner, visited_blue_copy,visited_red_copy)) {
                                            if (is_board_possible) is_board_possible = false;
                                            else is_board_possible = true;
                                            i = size;
                                            break;
                                        }
                                        else {
                                            if (is_board_possible) {
                                                is_board_possible = false;
                                                free_array(visited_blue_copy, size);
                                                free_array(visited_red_copy, size);
                                                i = size;
                                                break;
                                            }
                                            board[i][j] = blue_pawn_symbol;
                                        }

                                        free_array(visited_blue_copy, size);
                                        free_array(visited_red_copy, size);
                                    }
                                }
                            }

                            if (*blue_pawns_counter != *red_pawns_counter) is_board_possible = false;

                        }

                    } else is_board_possible = true;
                }
                else is_board_possible = true;

                if (is_board_possible) printf("YES\n");
                else printf("NO\n");

                // free memory
                free_array(board, size);
                free_array(visited_red, size);
                free_array(visited_blue, size);
                break;

            }
            default:
                break;

        }

        hexes->clear(); // free memory
        *query_id = 0;
        *symbol_id = 0;

    }

}
