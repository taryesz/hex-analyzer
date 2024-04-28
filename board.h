// this function will create a dynamic array representing the game board
int** create_board(stack* hexes, const int size) {

    // create a dynamic size x size 2D-array of integers
    int** board = create_array<int>(size);

    // get the head of the stack
    node* iterator = hexes->get_head();

    // while there are elements on the stack
    while (iterator != nullptr) {

        int x = iterator->get_position_x();
        int y = iterator->get_position_y();
        int content = iterator->get_content();

        board[x][y] = content;

        // get the next element
        iterator = iterator->get_next();

    }

    // return the filled out board
    return board;

}
