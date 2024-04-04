// this function sets all crucial variables to the default values
void reset_variables(stack* hexes, stack* middle_board_symbols, int *number_of_hexes, int* red_pawns_counter, int* blue_pawns_counter, int* empty_hexes_counter,int* query_id, int* symbol_id, int* hexes_in_line_counter, int* hexes_in_line, int* level, int* position_x, int* position_y, int* last_position_y, bool* finished_board_parsing, bool* pawn_detected, bool* middle_found_flag) {

    hexes->clear();
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
void launch_parser(stack* hexes, stack* middle_board_symbols, int *number_of_hexes, int* red_pawns_counter, int* blue_pawns_counter, int* empty_hexes_counter,int* query_id, int* symbol_id, int* hexes_in_line_counter, int* hexes_in_line, int* level, int* position_x, int* position_y, int* last_position_y, bool* finished_board_parsing, bool* pawn_detected, bool* middle_found_flag) {

    // input characters
    while (true) {

        // get a character
        int symbol = getchar();

        // if the character is EOF, stop the input, terminate the program
        if (symbol == INPUT_TERMINATOR) break;

        // if the character is a visible ascii, not some random whitespace
        if (symbol >= first_visible_ascii && symbol <= final_visible_ascii) { // && symbol != ignore_symbol

            if (symbol == ignore_symbol) {

                // TODO: NEW
                if (middle_board_symbols->get_head() && !(*middle_found_flag)) {
                    int content = middle_board_symbols->get_head()->get_content();
                    if ((content == hex_finish_detection_symbol || content == ignore_symbol) && middle_board_symbols->count() < 3) {
                        middle_board_symbols->push(ignore_symbol, UNDEFINED, UNDEFINED);
                    }
                    else middle_board_symbols->clear();
                }

                // if head == '>' or head == '-' :
                //      push(-)

            }

            // if the symbol is a '<', one more hex was found, which means the size is getting bigger
            else if (symbol == hex_detection_symbol) {

                middle_board_symbols->print();
                // TODO: NEW
                if (middle_board_symbols->get_head() && !(*middle_found_flag)) {
                    int content = middle_board_symbols->get_head()->get_content();
                    if (content == ignore_symbol) {
                        if (middle_board_symbols->get_head()->get_next()) {
                            content = middle_board_symbols->get_head()->get_next()->get_content();
                            if (content == ignore_symbol) {
                                if (middle_board_symbols->get_head()->get_next()->get_next()) {
                                    content = middle_board_symbols->get_head()->get_next()->get_next()->get_content();
                                    if (content == hex_finish_detection_symbol) {
                                        middle_board_symbols->clear();
                                        printf("here\n");
                                        *middle_found_flag = true;
                                        // TODO: FIX THE PROBLEM : WHY ISN'T THE FLAG TOGGLING?
                                    }
                                    else middle_board_symbols->clear();
                                }
                                else middle_board_symbols->clear();
                            }
                            else middle_board_symbols->clear();
                        }
                        else middle_board_symbols->clear();
                    }
                    else middle_board_symbols->clear();
                }

                // if head == '-' and next == '-' and next.next == '>' :
                //      clear stack
                //      middle_board_flag == true

                // if the parsing of a board is finished, reset the variables for the next one
                if (*finished_board_parsing) {
                    reset_variables(hexes, middle_board_symbols, number_of_hexes, red_pawns_counter, blue_pawns_counter, empty_hexes_counter, query_id, symbol_id, hexes_in_line_counter, hexes_in_line, level, position_x, position_y, last_position_y, finished_board_parsing, pawn_detected, middle_found_flag);
                }

                // increment the number of hexes: each '<' symbol means one hex
                ++(*number_of_hexes);

            }

            // if the symbol is a '>', check if this hex is empty or not
            else if (symbol == hex_finish_detection_symbol) {
                check_if_hex_empty(hexes, position_x, position_y, last_position_y, hexes_in_line_counter, hexes_in_line, level, empty_hexes_counter, pawn_detected, middle_found_flag);

                // TODO: NEW
                if (!(*middle_found_flag)) {
                    if (middle_board_symbols->get_head() == nullptr) {
                        middle_board_symbols->push(hex_finish_detection_symbol, UNDEFINED, UNDEFINED);
                    }
                    else if (middle_board_symbols->get_head()->get_content() != ignore_symbol) {
                        middle_board_symbols->push(hex_finish_detection_symbol, UNDEFINED, UNDEFINED);
                    }
                    else middle_board_symbols->clear();
                }

                // if head != '-' :
                    // push(>)
            }

            // if the symbol is a 'r', add the red pawn to the stack
            else if (symbol == red_pawn_symbol) {
                *pawn_detected = parse_hex(hexes, position_x, position_y, last_position_y, hexes_in_line_counter, hexes_in_line, level, red_pawns_counter, red_pawn_symbol, middle_found_flag);
            }

            // if the symbol is a 'b', add the blue pawn to the stack
            else if (symbol == blue_pawn_symbol) {
                *pawn_detected = parse_hex(hexes, position_x, position_y, last_position_y, hexes_in_line_counter, hexes_in_line, level, blue_pawns_counter, blue_pawn_symbol, middle_found_flag);
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
