// this function detects the moment when the program has parsed half of the board
// it's needed to set the new mechanism of coordinates assignment for the rest of the hexes
void check_for_middle_board(stack* middle_board_symbols, int symbol, bool* middle_found_flag, const int characters[MIDDLE_BOARD_SYMBOLS_COUNT]) {

    switch (symbol) {

        // if the symbol is a '-' ...
        case ignore_symbol: {

            // if the stack that stores middle board symbols is not empty and the middle of the board hasn't yet been found ...
            if (middle_board_symbols->get_head() && !(*middle_found_flag)) {

                int content = middle_board_symbols->get_head()->get_content(); // get the latest found board symbol

                // if this symbol is a '>' or a '-' and the amount of the symbols is less than 3 ...
                if ((content == hex_finish_detection_symbol || content == ignore_symbol) && middle_board_symbols->count() < MIDDLE_BOARD_SYMBOLS_COUNT) {
                    middle_board_symbols->push(ignore_symbol, UNDEFINED, UNDEFINED); // add new '-'
                }

                // otherwise, it's not the middle of the board, all the saved symbols have to be removed
                else middle_board_symbols->clear();

            }

            break;

        }

        // if the symbol is a '<' ...
        case hex_detection_symbol: {

            // if the stack is not empty and the middle of the board has not been found yet ...
            if (middle_board_symbols->get_head() && !(*middle_found_flag)) {

                // iterate through the defined sequence of characters
                node* iterator = middle_board_symbols->get_head();
                for (int i = 0; i < MIDDLE_BOARD_SYMBOLS_COUNT; i++) {

                    // if the found character is in the sequence, set the pointer to the next one in the sequence
                    if (iterator->get_content() == characters[i]) {
                        iterator = iterator->get_next();
                    }

                    // if at least one character differs, clear the stack and exit the function
                    else {
                        middle_board_symbols->clear();
                        return;
                    }

                }

                // if all the symbols match, set the flag and clear the stack
                middle_board_symbols->clear();
                *middle_found_flag = true;

            }

            break;

        }

        // if the symbol is '>' ...
        case hex_finish_detection_symbol: {

            // if the middle of the board hasn't yet been found ...
            if (!(*middle_found_flag)) {

                // if the stack is empty, add the symbol
                if (middle_board_symbols->get_head() == nullptr) middle_board_symbols->push(hex_finish_detection_symbol, UNDEFINED, UNDEFINED);

                // otherwise, clear the stack
                else middle_board_symbols->clear();

            }

            break;

        }

        default: break;

    }

}
