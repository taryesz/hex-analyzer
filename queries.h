#include "array.h"
#include "board.h"
#include "board-size.h"
#include "pawns-number.h"
#include "is-board-correct.h"
#include "is-game-over.h"
#include "is-board-possible.h"
#include "can-player-win-in-n-moves.h"
//#include "test.h"


// this function will store and return a query
const char* get_query(int query_id) {

    switch (query_id) {
        case board_size: return "BOARD_SIZE";
        case pawns_number: return "PAWNS_NUMBER";
        case is_board_correct: return "IS_BOARD_CORRECT";
        case is_game_over: return "IS_GAME_OVER";
        case is_board_possible: return "IS_BOARD_POSSIBLE";

        case can_red_win_in_1_move_with_naive_opponent: return "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT";
        case can_red_win_in_2_moves_with_naive_opponent: return "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT";

        case can_blue_win_in_1_move_with_naive_opponent: return "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT";
        case can_blue_win_in_2_moves_with_naive_opponent: return "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT";

        case can_red_win_in_1_move_with_perfect_opponent: return "CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT";
        case can_red_win_in_2_moves_with_perfect_opponent: return "CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT";

        case can_blue_win_in_1_move_with_perfect_opponent: return "CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT";
        case can_blue_win_in_2_moves_with_perfect_opponent: return "CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT";

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
            if (queries[*query_id][*symbol_id] == STRING_TERMINATOR) {
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

// this function compares the input letters with the defined queries and executes one when detected
void parse_query(stack* hexes, int symbol, int* query_id, int* symbol_id, const int* number_of_hexes, const int* red_pawns_counter, const int* blue_pawns_counter, bool* finished_board_parsing) {

    // if the provided query exists in the program's list of queries ...
    if (compare_queries(symbol, query_id, symbol_id)) {

        // update the last node's coords
        // [ because it always has the wrong ones and should be changed by  *
        // * taking the penultimate node's ones and incrementing Y-pos by 1 ]
        update_last_node_coords(hexes);

        // set the flag to true since the program is no longer parsing the board and the respective variables have to
        // get reset for the next board
        *finished_board_parsing = true;

        // if the query id is ...
        switch (*query_id) {
            case board_size: {
                get_board_size(*number_of_hexes, true);
                break;
            }
            case pawns_number: {
                get_pawns_number(red_pawns_counter, blue_pawns_counter, true);
                break;
            }
            case is_board_correct: {
                check_is_board_correct(*blue_pawns_counter, *red_pawns_counter, *number_of_hexes, true);
                break;
            }
            case is_game_over: {
                bool winner;
                check_is_game_over(hexes, blue_pawns_counter, red_pawns_counter, number_of_hexes, &winner, true);
                break;
            }
            case is_board_possible: {
                check_is_board_possible(hexes, blue_pawns_counter, red_pawns_counter, number_of_hexes, true);
                break;
            }
            case can_red_win_in_1_move_with_naive_opponent: {
//                printf("\n1\n");
                int tree_depth = 1;
                int number_of_moves = 1;
                int main_player = red_pawn_symbol;
                check_can_player_win_in_n_moves(hexes, (int) *blue_pawns_counter, (int) *red_pawns_counter, (int) *number_of_hexes, tree_depth, main_player, number_of_moves, false, true);
                break;
            }
            case can_red_win_in_2_moves_with_naive_opponent: {
//                printf("\n2\n");
                int tree_depth = 2;
                int number_of_moves = 2;
                int main_player = red_pawn_symbol;
                //check_can_player_win_in_n_moves(hexes, (int) *blue_pawns_counter, (int) *red_pawns_counter, (int) *number_of_hexes, tree_depth, main_player, number_of_moves, false, true);
                break;
            }
            case can_blue_win_in_1_move_with_naive_opponent: {
//                printf("\n3\n");
                int tree_depth = 1;
                int number_of_moves = 1;
                int main_player = blue_pawn_symbol;
                check_can_player_win_in_n_moves(hexes, (int) *blue_pawns_counter, (int) *red_pawns_counter, (int) *number_of_hexes, tree_depth, main_player, number_of_moves, false, true);
                break;
            }
            case can_blue_win_in_2_moves_with_naive_opponent: {
//                printf("\n4\n");
                int tree_depth = 2;
                int number_of_moves = 2;
                int main_player = blue_pawn_symbol;
                //check_can_player_win_in_n_moves(hexes, (int) *blue_pawns_counter, (int) *red_pawns_counter, (int) *number_of_hexes, tree_depth, main_player, number_of_moves, false, true);
                break;
            }
            case can_red_win_in_1_move_with_perfect_opponent: {
//                printf("\n5\n");
                int tree_depth = 1;
                int number_of_moves = 1;
                int main_player = red_pawn_symbol;
                check_can_player_win_in_n_moves(hexes, (int) *blue_pawns_counter, (int) *red_pawns_counter, (int) *number_of_hexes, tree_depth, main_player, number_of_moves, true, true);
                break;
            }
            case can_red_win_in_2_moves_with_perfect_opponent: {
//                printf("\n6\n");
                int tree_depth = 2;
                int number_of_moves = 2;
                int main_player = red_pawn_symbol;
                check_can_player_win_in_n_moves(hexes, (int) *blue_pawns_counter, (int) *red_pawns_counter, (int) *number_of_hexes, tree_depth, main_player, number_of_moves, true, true);
                break;
            }
            case can_blue_win_in_1_move_with_perfect_opponent: {
//                printf("\n7\n");
                int tree_depth = 1;
                int number_of_moves = 1;
                int main_player = blue_pawn_symbol;
                check_can_player_win_in_n_moves(hexes, (int) *blue_pawns_counter, (int) *red_pawns_counter, (int) *number_of_hexes, tree_depth, main_player, number_of_moves, true, true);
                break;
            }
            case can_blue_win_in_2_moves_with_perfect_opponent: {
//                printf("\n8\n");
                int tree_depth = 2;
                int number_of_moves = 2;
                int main_player = blue_pawn_symbol;
                check_can_player_win_in_n_moves(hexes, (int) *blue_pawns_counter, (int) *red_pawns_counter, (int) *number_of_hexes, tree_depth, main_player, number_of_moves, true, true);
                break;
            }
            default:
                break;
        }

        *query_id = 0;  // reset the ID for the next query comparison
        *symbol_id = 0; // reset the ID for the next query comparison

    }

}
