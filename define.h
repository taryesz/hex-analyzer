#define INPUT_TERMINATOR '|'
#define STRING_TERMINATOR '\0'
#define PAWNS_MAX_DIFFERENCE 1
#define UNDEFINED (-1)
#define OFFSET_FROM_BOARD_EDGE 1
#define NEIGHBOR_DISTANCE 1
#define OUT_OF_BOUNDS_COORDINATE 0
#define POSITIVE_RESULT 1
#define NEGATIVE_RESULT 0
#define NEUTRAL_RESULT 2
#define LAST_TREE_LEVEL 1
#define ABSOLUTE_ALPHA (-1)
#define ABSOLUTE_BETA 3

enum digit_ascii_range {
    first_digit_ascii = 48,
    final_digit_ascii = 57
};

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

    can_red_win_in_1_move_with_naive_opponent,
    can_red_win_in_2_moves_with_naive_opponent,

    can_red_win_in_1_move_with_perfect_opponent,
    can_red_win_in_2_moves_with_perfect_opponent,

    can_blue_win_in_1_move_with_naive_opponent,
    can_blue_win_in_2_moves_with_naive_opponent,

    can_blue_win_in_1_move_with_perfect_opponent,
    can_blue_win_in_2_moves_with_perfect_opponent,

    queries_quantity
};