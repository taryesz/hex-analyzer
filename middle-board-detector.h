void check_for_middle_board(stack* middle_board_symbols, int symbol, bool* middle_found_flag) {

    switch (symbol) {
        case ignore_symbol: {

            if (middle_board_symbols->get_head() && !(*middle_found_flag)) {

                int content = middle_board_symbols->get_head()->get_content();

                // if the last symbol on the stack is a '>' or a '-' and the amount of the symbols is less than 3 ...
                if ((content == hex_finish_detection_symbol || content == ignore_symbol) && middle_board_symbols->count() < MIDDLE_BOARD_SYMBOLS_COUNT) {
                    middle_board_symbols->push(ignore_symbol, UNDEFINED, UNDEFINED); // add new '-'
                }
                // otherwise, it's not the middle of the board, all the saved symbols have to be removed
                else middle_board_symbols->clear();
            }

            break;
        }
        case hex_detection_symbol: {

            // if the stack contains the following symbols: ">--", then the middle of the board is found - set the flag
            // if at least one character is not the one that is expected, clear the stack
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
                                    *middle_found_flag = true;
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

            break;
        }
        case hex_finish_detection_symbol: {

            // if the stack is empty and '>' is found, add it
            if (!(*middle_found_flag)) {
                if (middle_board_symbols->get_head() == nullptr) middle_board_symbols->push(hex_finish_detection_symbol, UNDEFINED, UNDEFINED);
                else middle_board_symbols->clear();
            }

            break;
        }
        default: break;

    }

}