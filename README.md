
# RPN Calculator

This project is an implementation of the Hex analyzer. 

The user can provide the program with a board and then type various commands to get needed information.

### First Example

Let's say you have the following board:

> <img width="200" alt="Screenshot 2024-05-03 at 10 50 59 PM" src="https://gist.github.com/assets/106448156/107ea2b9-f270-4030-a0ba-295d1364f4ae">

... and you want to find out its size.

To do that, input the board, and then type `BOARD_SIZE`

_**First input**_

> <img width="200" alt="Screenshot 2024-05-03 at 10 50 59 PM" src="https://gist.github.com/assets/106448156/107ea2b9-f270-4030-a0ba-295d1364f4ae">

_**Second input**_

> `BOARD_SIZE`

_**Output:**_

> `5`

### Second Example

What if you want to find out whether it's possible to win the game as the Red player by placing only one pawn, assuming that the opponent player makes the worst moves for themselves?

_**First input**_

> <img width="200" alt="Screenshot 2024-05-03 at 10 50 59 PM" src="https://gist.github.com/assets/106448156/107ea2b9-f270-4030-a0ba-295d1364f4ae">

_**Second input**_

> CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT

_**Output:**_

> NO

## Running Tests

This repository contains a folder called "tests" where you can find 10 different `.in` files with various inputs and corresponding `.out` files with the correct outputs.