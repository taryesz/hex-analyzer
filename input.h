// this function sets all crucial variables to the default values
void reset_variables(stack* hexes, int *number_of_hexes, int* red_pawns_counter, int* blue_pawns_counter, int* empty_hexes_counter,int* query_id, int* symbol_id, int* level_counter, int* level, int* position_x, int* position_y, bool* finished_board_parsing, bool* pawn_detected) {

    hexes->clear();
    *number_of_hexes = 0;
    *red_pawns_counter = 0;
    *blue_pawns_counter = 0;
    *empty_hexes_counter = 0;
    *query_id = 0;
    *symbol_id = 0;
    *level_counter = 0;
    *level = 1;
    *position_x = 0;
    *position_y = 0;
    *finished_board_parsing = false;
    *pawn_detected = false;

}

// this function handles the whole execution of the program, i.e. accepts input from a user and checks what it received
void launch_parser(stack* hexes, int *number_of_hexes, int* red_pawns_counter, int* blue_pawns_counter, int* empty_hexes_counter,int* query_id, int* symbol_id, int* level_counter, int* level, int* position_x, int* position_y, bool* finished_board_parsing, bool* pawn_detected) {

    // input characters
    while (true) {

        // get a character
        int symbol = getchar();

        // if the character is EOF, stop the input, terminate the program
        if (symbol == INPUT_TERMINATOR) break;

        // if the character is a visible ascii, not some random whitespace
        if (symbol >= first_visible_ascii && symbol <= final_visible_ascii && symbol != ignore_symbol) {

            // if the symbol is a '<', one more hex was found, which means the size is getting bigger
            if (symbol == hex_detection_symbol) {

                // if the parsing of a board is finished, reset the variables for the next one
                if (*finished_board_parsing) {
                    reset_variables(hexes, number_of_hexes, red_pawns_counter, blue_pawns_counter, empty_hexes_counter, query_id, symbol_id, level_counter, level, position_x, position_y, finished_board_parsing, pawn_detected);
                }

                // increment the number of hexes: each '<' symbol means one hex
                ++(*number_of_hexes);

            }

            // if the symbol is a '>', check if this hex is empty or not
            else if (symbol == hex_finish_detection_symbol) {
                check_if_hex_empty(hexes, position_x, position_y, level_counter, level, empty_hexes_counter, pawn_detected);
            }

            // if the symbol is a 'r', add the red pawn to the stack
            else if (symbol == red_pawn_symbol) {
                *pawn_detected = parse_hex(hexes, position_x, position_y, level_counter, level, red_pawns_counter, red_pawn_symbol);
            }

            // if the symbol is a 'b', add the blue pawn to the stack
            else if (symbol == blue_pawn_symbol) {
                *pawn_detected = parse_hex(hexes, position_x, position_y, level_counter, level, blue_pawns_counter, blue_pawn_symbol);
            }

            // if the symbol is a capital letter, the program is about to start parsing a query
            else if ((symbol >= first_capital_letter_ascii && symbol <= final_capital_letter_ascii) || symbol == underscore) {
                parse_query(hexes, symbol, query_id, symbol_id, number_of_hexes, red_pawns_counter, blue_pawns_counter, finished_board_parsing);
            }

        }

        // if the character is a whitespace / invisible symbol, ignore it and get the next symbol
        else continue;

    }


}
