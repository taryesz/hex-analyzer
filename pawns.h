// this function adds a hex to the stack
bool parse_hex(stack* hexes, int* position_x, int* position_y, int* last_position_y, int* hexes_in_line_counter, int* hexes_in_line, int* level, int* n_pawns_counter, int content, const bool* middle_found_flag) {

    // add the hex
    hexes->push(content, *position_x, *position_y);

    // move to the next hex in the row (right neighbor)
    ++(*hexes_in_line_counter);

    // if there is no right neighbor left
    if (*hexes_in_line_counter == *hexes_in_line) {

        // move to the next level
        ++(*level);

        // if the middle of the board was found, the board will now shrink in size to the bottom
        if (*middle_found_flag) {

            // update the coords [ according to a discovered by me formula ]
            *position_x = *level - hexes->get_head()->get_position_x();
            *position_y = *level - hexes->get_head()->get_position_y() - 1;

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
void check_if_hex_empty(stack* hexes, int* position_x, int* position_y, int* last_position_y, int* hexes_in_line_counter, int* hexes_in_line, int* level, int* empty_hexes_counter, bool* pawn_detected, bool* middle_found_flag) {

    // if no pawn was detected in the node, add a '.'
    if (!(*pawn_detected)) *pawn_detected = parse_hex(hexes, position_x, position_y, last_position_y, hexes_in_line_counter, hexes_in_line, level, empty_hexes_counter, empty_hex_symbol, middle_found_flag);

    // otherwise, a pawn was already inserted, don't do anything
    else *pawn_detected = false;

}

// this function adapts the last node's coords
void update_last_node_coords(stack* hexes) {

    // get the head of the stack
    node* hex = hexes->get_head();

    // if the head exists ...
    if (hex != nullptr) {

        // if there are more than one node on the board
        if (hex->get_next() != nullptr) {

            // get the coords of the penultimate hex node
            int updated_x = hex->get_next()->get_position_x();
            int updated_y = hex->get_next()->get_position_y() + 1; // note: the Y-coord is increased by one

            // set the new coords for the last hex node in the stack
            hex->set_position_x(updated_x);
            hex->set_position_y(updated_y);

            // explanation: we need this function, since the program gets all the hexes diagonally and so the order of coords is messed up
            // e.g. if the penultimate node had coords (1, 0), the final one would have coords (2, 0) or something like that [ and not (1, 1) ]
            // ---> it's all due to the fact that the program assumes there are still more nodes to be parsed, but this function
            // is a way to tell the program: "hey, this was the last one".

        }
    }

}
