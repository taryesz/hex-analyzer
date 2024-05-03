#define INPUT_TERMINATOR '|'
#define STRING_TERMINATOR '\0'
#define PAWNS_MAX_DIFFERENCE 1
#define UNDEFINED (-1)
#define OFFSET_FROM_BOARD_EDGE 1
#define NEIGHBOR_DISTANCE 1
#define OUT_OF_BOUNDS_COORDINATE 0
#define MIDDLE_BOARD_SYMBOLS_COUNT 3
#define SIZE 11
#define MINIMAL_TREE_DEPTH 1

enum total_moves {
    maximizing_case_total_moves = 4,
    minimizing_case_total_moves = 3,
    one_move_total_moves_factor = 2
};

enum visible_ascii_range {
    first_visible_ascii = 32,
    final_visible_ascii = 126
};

enum commands {
    first_capital_letter_ascii = 65,
    final_capital_letter_ascii = 90,
    first_digit_ascii = 48,
    final_digit_ascii = 57,
    underscore = '_'
};

enum board {
    hex_detection_symbol = '<',
    hex_finish_detection_symbol = '>',
    empty_hex_symbol = '.',
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
    can_red_win_in_1_move_with_naive_opponent,
    can_red_win_in_2_moves_with_naive_opponent,
    can_blue_win_in_1_move_with_naive_opponent,
    can_blue_win_in_2_moves_with_naive_opponent,
    can_red_win_in_1_move_with_perfect_opponent,
    can_blue_win_in_1_move_with_perfect_opponent,
    can_red_win_in_2_moves_with_perfect_opponent,
    can_blue_win_in_2_moves_with_perfect_opponent,
    queries_quantity
};
