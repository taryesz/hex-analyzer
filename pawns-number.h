// this function calculates how many pawns the board contains
int get_pawns_number(const int *red_pawns_counter, const int *blue_pawns_counter, bool print_the_result = false) {
    const int final_pawns_number = *red_pawns_counter + *blue_pawns_counter;
    if (print_the_result) printf("%d\n", final_pawns_number);
    return final_pawns_number;
}
