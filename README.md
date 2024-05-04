
# Hex Analyzer

This project is an implementation of the Hex analyzer. 

The user can provide the program with a board and then type various commands to get needed information.

### First Example

Let's say you have the following board:

> ![Hex board example of size 5x5](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAYoAAAEmCAYAAAB8oNeFAAAKrGlDQ1BJQ0MgUHJvZmlsZQAASImVlwdQU+kWgP9700NCSwhFSuhNegsgJYQWQOnVRkgChBJiICiIqMjiCqwoIiLYQFdFFFwLIKIiotgWBQv2BVkUlHWxICoq7wJD2N037715Z+bM+e6555z//)

... and you want to find out its size.

To do that, input the board, and then type `BOARD_SIZE`

_**First input**_

> ![Hex board example of size 5x5](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAYoAAAEmCAYAAAB8oNeFAAAKrGlDQ1BJQ0MgUHJvZmlsZQAASImVlwdQU+kWgP9700NCSwhFSuhNegsgJYQWQOnVRkgChBJiICiIqMjiCqwoIiLYQFdFFFwLIKIiotgWBQv2BVkUlHWxICoq7wJD2N037715Z+bM+e6555z//)

_**Second input**_

> `BOARD_SIZE`

_**Output:**_

> `5`

### Second Example

What if you want to find out whether it's possible to win the game as the Red player by placing only one pawn, assuming that the opponent player makes the worst moves for themselves?

_**First input**_

> ![Hex board example of size 5x5](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAYoAAAEmCAYAAAB8oNeFAAAKrGlDQ1BJQ0MgUHJvZmlsZQAASImVlwdQU+kWgP9700NCSwhFSuhNegsgJYQWQOnVRkgChBJiICiIqMjiCqwoIiLYQFdFFFwLIKIiotgWBQv2BVkUlHWxICoq7wJD2N037715Z+bM+e6555z//)

_**Second input**_

> `CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT`

_**Output:**_

> `NO`

## Running Tests

This repository contains a folder called "tests" where you can find 10 different `.in` files with various inputs and corresponding `.out` files with the correct outputs.