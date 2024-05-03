// this function returns the counted board size
int get_board_size(int number_of_hexes, bool print_the_result = false) {
    int size = (int) sqrt(number_of_hexes); // the board is always of size AxA, so just get the root
    if (print_the_result) printf("%d\n", size);
    return size;
}
