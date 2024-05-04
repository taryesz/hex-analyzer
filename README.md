
# Hex Analyzer

This project is an implementation of the Hex analyzer. 

The user can provide the program with a board and then type various commands to get needed information.

### First Example

Let's say you have the following board:

> <img width="197" alt="Hex board example of size 5x5" src="https://github.com/taryesz/hex-game/assets/106448156/a3c8811f-1fc6-4065-acf0-b9fec174fa25">

... and you want to find out its size.

To do that, input the board, and then type `BOARD_SIZE`

_**First input**_

> <img width="197" alt="Hex board example of size 5x5" src="https://github.com/taryesz/hex-game/assets/106448156/a3c8811f-1fc6-4065-acf0-b9fec174fa25">

_**Second input**_

> `BOARD_SIZE`

_**Output:**_

> `5`

### Second Example

What if you want to find out whether it's possible to win the game as the Red player by placing only one pawn, assuming that the opponent player makes the worst moves for themselves?

_**First input**_

> <img width="197" alt="Hex board example of size 5x5" src="https://github.com/taryesz/hex-game/assets/106448156/a3c8811f-1fc6-4065-acf0-b9fec174fa25">

_**Second input**_

> `CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT`

_**Output:**_

> `NO`

## Available Queries

There are a couple of commands you can type in to get various board data:

- `BOARD_SIZE` - shows the size of the board, the length of a side
- `PAWNS_NUMBER` - shows the amount of pawns placed on the board
- `IS_BOARD_CORRECT` - checks if the number of placed pawns of both players are correct (e.g. there cannot be a situation where there are 12 Blues and only 1 Red)
- `IS_GAME_OVER` - checks if any of the players wins
- `IS_BOARD_POSSIBLE` - checks if the player, who is considered a winner of the game, has only _**one**_ winning path
- `CAN_#_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT` & `CAN_#_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT` - checks if a player (# - either `RED` or `BLUE`) can win the game by placing only 1 (or 2) of their pawns, considering that the opponent player makes the worst moves.

## Running Tests

This repository contains a folder called "tests" where you can find 10 different `.in` files with various inputs and corresponding `.out` files with the correct outputs.