# Numerical Tic-Tac-Toe

CUHK ENGG1110 - Problem Solving by Programming - An artificial intelligence agent driven with heuristic and alpha-beta pruning approaches. 

## (i)	Naïve Approach

### [ 25259 Games, Winning: 43.12%, Losing: 6.95% ]

(a) Rules for winning - ``checkWinningMove()``

In order to win, AI should check for any lines that would yield a win. That is, AI will check for horizontals, verticals and diagonals and place the correct number if available to constitute a win.

Note that AI as an even player could only place even numbers 2, 4, 6, 8 which is unused.

(b) Rules for defending - ``checkDefendMove()``

Place a number so as to block the second player from winning. AI should check for any lines that would cause losing. It is apparently better to continue the game, and do not put numbers that would cause immediate win for the first player (user).

Note that AI would only constitute a valid defend if and only if the first player can win as they have the right number on hand. In this program, for simplicity, we choose the first available move to defend, but it can’t be considered as the best move.

(c) Rules for no good decision: A move without immediate losing - ``checkPossibleMove(..., 1)``

Find any place that will not cause immediate winning for player 1 in the subsequent step.

(d) Rules for no good decision: All moves are bad; they form a win for player 1 - ``checkPossibleMove(..., 0)``

> We could only hope that the first player never sees the winning move.

## (ii) Alpha-Beta Pruning

### [ 19104 Games, Winning: 56.46%, Losing: 0.19% ]

# Validity Detection

Simple string manipulations should work well enough.

Flow diagram is used for easy references and for course evaluation purpose showcasing the ability.

![image](https://github.com/SWongHF/Numerical-Tic-Tac-Toe/assets/36600923/f5bc104f-7255-44d7-9045-a8014d0cbfe3)


# References

[1] 	George Markowsky, “NUMERICAL TIC-TAC-TOE – II,” J. Recreational Mathematics, Vol. 22(3) (1990): 192-200.

[2]	“Minimax Algorithm,” Wikipedia, updated November 23, 2022, accessed December 1, 2022, https://en.wikipedia.org/wiki/Minimax#Minimax_algorithm_with_alternate_moves.

[3]	“A normal Tic-tac-toc AI,” GeorgeSeif on GitHub, April 22, 2017, accessed November 22, 2022, https://github.com/GeorgeSeif/Tic-Tac-Toe-AI.

# License

This project is currently under the Creative Commons CC BY-NC license. It is not intended for commercial use. If you wish to use this project for academic purposes, please follow the guidelines of your institution to prevent academic dishonesty and plagiarism.

