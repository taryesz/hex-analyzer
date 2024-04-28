// this function adds a hex to the stack
bool parse_hex(int hexes[SIZE][SIZE], int* position_x, int* position_y, int* last_position_y, int* hexes_in_line_counter, int* hexes_in_line, int* level, int* n_pawns_counter, int content, const bool* middle_found_flag, int* most_recent_x, int* most_recent_y) {

    // add the hex
    hexes[*position_x][*position_y] = content;

    *most_recent_x = *position_x;
    *most_recent_y = *position_y;

    // move to the next hex in the row (right neighbor)
    ++(*hexes_in_line_counter);

    // if there is no right neighbor left
    if (*hexes_in_line_counter == *hexes_in_line) {

        // move to the next level
        ++(*level);

        // if the middle of the board was found, the board will now shrink in size to the bottom
        if (*middle_found_flag) {

            // update the coords [ according to a discovered by me formula ]
            *position_x = *level - *most_recent_x;
            *position_y = *level - *most_recent_y - 1;

            // since the board is shrinking, there will be fewer and fewer hexes over time
            --(*hexes_in_line);

            // reset the hex counter
            *hexes_in_line_counter = 0;

        }

        // if the board is still broadening ...
        else {

            // reset the coords, i.e. move one line deeper into the board and move to the very left node
            *position_x = 0;
            *position_y = ++(*last_position_y);

            // reset the hex counter
            *hexes_in_line_counter = 0;

            // increment the variable: each level has one more hex than the previous level
            ++(*hexes_in_line);

        }

    }

    // if there is a right neighbor
    else {

        // if the first symbol from the row is being parsed, the program has to save its Y-coord
        // this is because the movement in the array is performed diagonally
        if (*hexes_in_line_counter == 0) *last_position_y = *position_y;

        // update the coordinates
        ++(*position_x);
        --(*position_y);

    }

    // update the number of found pawns / empty hexes
    ++(*n_pawns_counter);

    // if the pushed symbol was an empty hex, no pawn was found
    if (content == empty_hex_symbol) return false;

    // a pawn was found
    else return true;

}

// this function checks if the parsed hex node is empty
void check_if_hex_empty(int hexes[SIZE][SIZE], int* position_x, int* position_y, int* last_position_y, int* hexes_in_line_counter, int* hexes_in_line, int* level, int* empty_hexes_counter, bool* pawn_detected, bool* middle_found_flag, int* most_recent_x, int* most_recent_y) {

    // if no pawn was detected in the node, add a '.'
    if (!(*pawn_detected)) *pawn_detected = parse_hex(hexes, position_x, position_y, last_position_y, hexes_in_line_counter, hexes_in_line, level, empty_hexes_counter, empty_hex_symbol, middle_found_flag, most_recent_x, most_recent_y);

    // otherwise, a pawn was already inserted, don't do anything
    else *pawn_detected = false;

}
