// this function sets all crucial variables to the default values for the next board to be parsed
void reset_variables(stack* middle_board_symbols, int *number_of_hexes, int* red_pawns_counter, int* blue_pawns_counter, int* empty_hexes_counter,int* query_id, int* symbol_id, int* hexes_in_line_counter, int* hexes_in_line, int* level, int* position_x, int* position_y, int* last_position_y, bool* finished_board_parsing, bool* pawn_detected, bool* middle_found_flag) {

    *number_of_hexes = 0;
    *red_pawns_counter = 0;
    *blue_pawns_counter = 0;
    *empty_hexes_counter = 0;
    *query_id = 0;
    *symbol_id = 0;
    *hexes_in_line_counter = 0;
    *hexes_in_line = 1;
    *level = 0;
    *position_x = 0;
    *position_y = 0;
    *last_position_y = 0;
    *finished_board_parsing = false;
    *pawn_detected = false;
    *middle_found_flag = false;
    middle_board_symbols->clear();

}

// this function handles the whole execution of the program, i.e. accepts input from a user and checks what it received
void launch_parser(int hexes[SIZE][SIZE], stack* middle_board_symbols, int *number_of_hexes, int* red_pawns_counter, int* blue_pawns_counter, int* empty_hexes_counter,int* query_id, int* symbol_id, int* hexes_in_line_counter, int* hexes_in_line, int* level, int* position_x, int* position_y, int* last_position_y, bool* finished_board_parsing, bool* pawn_detected, bool* middle_found_flag, int* most_recent_x, int* most_recent_y, int characters[MIDDLE_BOARD_SYMBOLS_COUNT]) {

    // input characters
    while (true) {

        // get a character
        int symbol = getchar();

        // if the character is EOF, stop the input, terminate the program
        if (symbol == INPUT_TERMINATOR) break;

        // if the character is a visible ascii, not some random whitespace
        if (symbol >= first_visible_ascii && symbol <= final_visible_ascii) { // && symbol != ignore_symbol

            if (symbol == ignore_symbol) {
                // check if the middle of the board is being parsed
                check_for_middle_board(middle_board_symbols, symbol, middle_found_flag, characters);
            }

            // if the symbol is a '<', one more hex was found, which means the size is getting bigger
            else if (symbol == hex_detection_symbol) {

                // check if the middle of the board is being parsed
                check_for_middle_board(middle_board_symbols, symbol, middle_found_flag, characters);

                // if the parsing of a board is finished, reset the variables for the next one
                if (*finished_board_parsing) reset_variables(middle_board_symbols, number_of_hexes, red_pawns_counter, blue_pawns_counter, empty_hexes_counter, query_id, symbol_id, hexes_in_line_counter, hexes_in_line, level, position_x, position_y, last_position_y, finished_board_parsing, pawn_detected, middle_found_flag);

                // increment the number of hexes: each '<' symbol means one hex
                ++(*number_of_hexes);

            }

            // if the symbol is a '>', check if this hex is empty or not
            else if (symbol == hex_finish_detection_symbol) {
                check_if_hex_empty(hexes, position_x, position_y, last_position_y, hexes_in_line_counter, hexes_in_line, level, empty_hexes_counter, pawn_detected, middle_found_flag, most_recent_x, most_recent_y);
                check_for_middle_board(middle_board_symbols, symbol, middle_found_flag, characters); // check if the middle of the board is being parsed
            }

            // if the symbol is a 'r', add the red pawn to the stack
            else if (symbol == red_pawn_symbol) {
                *pawn_detected = parse_hex(hexes, position_x, position_y, last_position_y, hexes_in_line_counter, hexes_in_line, level, red_pawns_counter, red_pawn_symbol, middle_found_flag, most_recent_x, most_recent_y);
            }

            // if the symbol is a 'b', add the blue pawn to the stack
            else if (symbol == blue_pawn_symbol) {
                *pawn_detected = parse_hex(hexes, position_x, position_y, last_position_y, hexes_in_line_counter, hexes_in_line, level, blue_pawns_counter, blue_pawn_symbol, middle_found_flag, most_recent_x, most_recent_y);
            }

            // if the symbol is a capital letter, the program is about to start parsing a query
            else if ((symbol >= first_capital_letter_ascii && symbol <= final_capital_letter_ascii) || symbol == underscore || (symbol >= first_digit_ascii && symbol <= final_digit_ascii)) {
                parse_query(hexes, symbol, query_id, symbol_id, number_of_hexes, red_pawns_counter, blue_pawns_counter, finished_board_parsing);
            }

        }

        // if the character is a whitespace / invisible symbol, ignore it and get the next symbol
        else continue;

    }

}
