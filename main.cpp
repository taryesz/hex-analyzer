#include <iostream>
#include "stack.h"
#include "pawns.h"
#include "queries.h"
#include "input.h"


int main() {

    // create a stack to store the board hexes and their coords
    auto* hexes = new stack();

    // create and initiate variables that will store a hex's position coords
    int position_x = 0;
    int position_y = 0;

    // create and initiate a variable that will help the program know when to "reset" the coords
    // i.e. when the last hex in the row is parsed, the program needs to "jump" all the way to the left
    // and one level lower
    int level = 1;

    // create and initiate a variable that will count until the final element of the level is reached
    int level_counter = 0;

    // create and initiate a flag that will tell the program whether to add a '.' to the stack, or a pawn
    bool pawn_detected = false;

    // create and initialize a variable that will store the size of the board
    // warning: it stores the number of hexes, i.e. size squared - to get the normal size, use sqrt()
    int number_of_hexes = 0;

    // create and initialize a variable that will store the number of pawns of the red player
    int red_pawns_counter = 0;

    // create and initialize a variable that will store the number of pawns of the blue player
    int blue_pawns_counter = 0;

    // create and initiate a variable that will store the number of empty hexes
    int empty_hexes_counter = 0;

    // create and initiate a variable that will store the last successful comparison's function id
    // for the program to know where to keep looking for similarities between the input query and the reserved ones
    int query_id = 0;

    // create and initiate a variable that will store the last successful comparison's symbol id
    // for the program to know where to keep looking for similarities between the input query and the reserved ones
    int symbol_id = 0;

    // create and initiate a flag that will tell the program whether to reset all of the above variables for the next board or not yet
    bool finished_board_parsing = false;

    /* ---------------------------------------------------------------------------------------------------------- */

    launch_parser(hexes, &number_of_hexes, &red_pawns_counter, &blue_pawns_counter, &empty_hexes_counter, &query_id, &symbol_id, &level_counter, &level, &position_x, &position_y, &finished_board_parsing, &pawn_detected);

    return 0;

}
