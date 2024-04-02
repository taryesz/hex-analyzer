#include <iostream>
#include "define.h"
#include "queries.h"


int main() {

    // create and initialize a variable that will store the size of the board
    // warning: it stores the number of hexes, i.e. size squared - to get the normal size, use sqrt()
    int size = 0;

    // create and initialize a variable that will store the number of pawns of the red player
    int red_pawns_counter = 0;

    // create and initialize a variable that will store the number of pawns of the blue player
    int blue_pawns_counter = 0;

    //
    int query_id = 0;

    int symbol_id = 0;

    bool finished_board_parsing = false;

    // input characters
    while (true) {

        // get a character
        int symbol = getchar();

        // if the character is EOF, stop the input, terminate the program
        if (symbol == INPUT_TERMINATOR) break;

        // if the character is a visible ascii, not some random whitespace
        if (symbol >= first_visible_ascii && symbol <= final_visible_ascii) {

            // if the symbol is a '<', one more hex was found, which means the size is getting bigger
            if (symbol == hex_detection_symbol) {
                if (finished_board_parsing) {
                    size = 0;
                    red_pawns_counter = 0;
                    blue_pawns_counter = 0;
                    query_id = 0;
                    symbol_id = 0;
                    finished_board_parsing = false;
                }
                ++size;
            }

            // if the symbol is a 'r', more of a red player's pawns were found
            else if (symbol == red_pawn_symbol) ++red_pawns_counter;

            // if the symbol is a 'b', more of a blue player's pawns were found
            else if (symbol == blue_pawn_symbol) ++blue_pawns_counter;

            // if the symbol is a capital letter, the program is about to start parsing a query
            else if ((symbol >= first_capital_letter_ascii && symbol <= final_capital_letter_ascii) || symbol == underscore) {

                // if a query detected ...
                if(compare_queries(symbol, &query_id, &symbol_id)) {

                    finished_board_parsing = true;

                    switch (query_id) {
                        case board_size: {
                            const int final_board_size = (int) sqrt(size);
                            printf("%d\n", final_board_size);
                            break;
                        }
                        case pawns_number: {
                            const int final_pawns_number = red_pawns_counter + blue_pawns_counter;
                            printf("%d\n", final_pawns_number);
                            break;
                        }
                        case is_board_correct:
                            (abs(blue_pawns_counter - red_pawns_counter) > PAWNS_MAX_DIFFERENCE) ? printf("NO\n") : printf("YES\n");
                            break;
//                        case is_board_possible:
//                            break;
//                        case can_red_win_in_n_move_with_naive_opponent:
//                            break;
//                        case can_red_win_in_n_move_with_perfect_opponent:
//                            break;
                        default:
                            break;
                    }

                    query_id = 0;
                    symbol_id = 0;

                }

            }

        }

        // if the character is a whitespace / invisible symbol, ignore it and get the next symbol
        else continue;

    }

    return 0;

}
