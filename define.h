#define INPUT_TERMINATOR EOF
#define STRING_TERMINATOR '\n'
#define PAWNS_MAX_DIFFERENCE 1
#define UNDEFINED (-1)
#define OFFSET_FROM_BOARD_EDGE 1
#define NUMBER_OF_PLAYERS 2


enum visible_ascii_range {
    first_visible_ascii = 32,
    final_visible_ascii = 126
};

enum capital_letters_ascii_range {
    first_capital_letter_ascii = 65,
    final_capital_letter_ascii = 90,
    underscore = '_'
};

enum board {
    hex_detection_symbol = '<',
    hex_finish_detection_symbol = '>',
    default_symbol = '.',
    ignore_symbol = '-'
};

enum player {
    red_pawn_symbol = 'r',
    blue_pawn_symbol = 'b',
};

enum query {
    board_size,
    pawns_number,
    is_board_correct,
    is_game_over,
    is_board_possible,
    can_red_win_in_n_move_with_naive_opponent,
    can_red_win_in_n_move_with_perfect_opponent,
    queries_quantity
};