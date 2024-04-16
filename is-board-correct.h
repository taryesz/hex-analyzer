// this function checks if the amount of blue and red pawns is possible
bool check_is_board_correct(int blue_pawns_counter, int red_pawns_counter, int number_of_hexes, bool print_the_result = false) {

    // create a variable that will store the function's result
    bool result;

    // if there are more blues than reds, it's not possible so false
    if (blue_pawns_counter > red_pawns_counter) result = false;

    // if there is only one hex on the board, and it's a blue one, can't be because the game starts the red one
    else if (number_of_hexes == 1 && (!red_pawns_counter && blue_pawns_counter)) result = false;

    // if there is only one hex on the board, and it's a red one, it's a possible scenario
    else if (number_of_hexes == 1 && (!blue_pawns_counter && red_pawns_counter)) result = true;

    // if none of the above ...
    else {

        // if the difference in the amount of blue and red pawns is greater than one, can't be
        if (abs(blue_pawns_counter - red_pawns_counter) > PAWNS_MAX_DIFFERENCE) result = false;

        // otherwise, everything's fine
        else result = true;

    }

    // if the result is positive, ( and if the program needs it printed, print it ) return true
    if (result) {
        if (print_the_result) printf("YES\n");
        return true;
    }

        // if the result is negative, ( and if the program needs it printed, print it ) return false
    else {
        if (print_the_result) printf("NO\n");
        return false;
    }

}
