# Game - Move Simulation

## Description

This project simulates a game where possible moves for two players on the board are analyzed. The program calculates the game states and determines if either player can win in one or two moves against a naive or perfect opponent. For each board, the program evaluates the following aspects:

- The correctness of the board.
- Whether the game is over.
- If a player can win in one or two moves depending on the opponent's level.


## Input Format

The input consists of the following elements:

- **Board**: The game is represented using strings that describe the positions of the pawns.
- **Additional information**:
   - `BOARD_SIZE` – size of the board.
   - `PAWNS_NUMBER` – number of pawns on the board.
   - `IS_BOARD_CORRECT` – whether the board configuration is correct.
   - `IS_GAME_OVER` – whether the game has ended.
   - `IS_BOARD_POSSIBLE` – whether the current board configuration is possible.
   - `CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT` – whether red can win in 1 move against a naive opponent.
   - `CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT` – whether blue can win in 1 move against a naive opponent.
   - `CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT` – whether red can win in 2 moves against a naive opponent.
   - `CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT` – whether blue can win in 2 moves against a naive opponent.
   - `CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT` – whether red can win in 1 move against a perfect opponent.
   - `CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT` – whether blue can win in 1 move against a perfect opponent.
   - `CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT` – whether red can win in 2 moves against a perfect opponent.
   - `CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT` – whether blue can win in 2 moves against a perfect opponent.

## Example

### Example 1

#### Input
Input

 ---
<   >
 ---
BOARD_SIZE

PAWNS_NUMBER

IS_BOARD_CORRECT

IS_GAME_OVER

IS_BOARD_POSSIBLE

CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT

CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT

#### Output 
1

0

YES

NO

YES

YES
NO
NO
NO

YES
NO
NO
NO

### Example 1
#### Input
---
 --<   >--
<   >-<   >
 --<   >--
    ---
BOARD_SIZE

PAWNS_NUMBER

IS_BOARD_CORRECT

IS_GAME_OVER

IS_BOARD_POSSIBLE

CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT

CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
#### Output
2

0

YES

NO

YES

NO
NO
YES
YES

NO
NO
YES
NO

### Example 3
#### Input 
---
       --< b >--
    --< r >-< b >--
 --< r >-< r >-< b >--
< b >-< b >-< r >-< b >
 --< r >-< b >-< b >--
    --< r >-< r >--
       --< r >--
          ---
BOARD_SIZE

PAWNS_NUMBER

IS_BOARD_CORRECT

IS_GAME_OVER

IS_BOARD_POSSIBLE

CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT

CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
#### Output

4

16

YES

YES RED

NO

NO
NO
NO
NO

NO
NO
NO
NO

### Example 3
#### Input 
---
                            --<   >--
                         --<   >-<   >--
                      --<   >-<   >-<   >--
                   --< r >-<   >-<   >-< b >--
                --<   >-<   >-<   >-<   >-<   >--
             --<   >-< r >-<   >-<   >-< b >-<   >--
          --<   >-<   >-< r >-<   >-< b >-<   >-<   >--
       --<   >-<   >-<   >-< r >-< b >-<   >-<   >-<   >--
    --<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >--
 --<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >--
<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >-<   >
 --<   >-<   >-<   >-<   >-< b >-< r >-<   >-<   >-<   >-<   >--
    --<   >-<   >-<   >-< b >-<   >-<   >-<   >-<   >-<   >--
       --<   >-<   >-<   >-<   >-< r >-<   >-<   >-<   >--
          --<   >-<   >-< b >-<   >-< r >-<   >-<   >--
             --<   >-<   >-<   >-<   >-<   >-<   >--
                --<   >-< b >-<   >-< r >-<   >--
                   --< b >-<   >-<   >-< r >--
                      --<   >-<   >-<   >--
                         --<   >-<   >--
                            --<   >--
                               ---
BOARD_SIZE

PAWNS_NUMBER

IS_BOARD_CORRECT

IS_GAME_OVER

IS_BOARD_POSSIBLE

CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT

CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT

#### Output
11

18

YES

NO

YES

NO
NO
YES
YES

NO
NO
YES
NO
