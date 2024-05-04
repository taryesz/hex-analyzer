
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

## Running Tests

This repository contains a folder called "tests" where you can find 10 different `.in` files with various inputs and corresponding `.out` files with the correct outputs.