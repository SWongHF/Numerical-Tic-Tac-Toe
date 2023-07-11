/**
 * ENGG1110 Problem Solving by Programming
 *
 * Course Project
 *
 * I declare that the project here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   https://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name  : Hok Fong, WONG
 * Student ID    : 1155189917
 * Class/Section : ENGG1110A
 * Date          : 2022.11.07
 */

#include <stdio.h>
void printInfo(int gameBoard[3][3], int numbers[9])
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        printf("|");
        for (j = 0; j < 3; j++)
        {
            if (gameBoard[i][j] == 0)
                printf(" |");
            else
                printf("%d|", gameBoard[i][j]);
        }
        printf("\n");
    }
    printf("Unused numbers:\n");
    int flag = 0;
    for (i = 0; i < 9; i++)
        if (numbers[i] == 0)
        {
            if (flag)
                printf(" %d", i + 1);
            else
                printf("%d", i + 1);
            flag = 1;
        }
    printf("\n");
}
int hasWinner(int gameBoard[3][3])
{
    int sum = 0, flag = 1, row, col;
    // horizontal sum
    for (row = 0; row < 3; row++)
    {
        sum = 0;
        flag = 1;
        for (col = 0; col < 3; col++)
        {
            if (gameBoard[row][col] == 0)
                flag = 0;
            sum += gameBoard[row][col];
        }
        if (flag == 1 && sum == 15)
            return 1;
    }
    for (col = 0; col < 3; col++)
    {
        sum = 0;
        flag = 1;
        for (row = 0; row < 3; row++)
        {
            if (gameBoard[row][col] == 0)
                flag = 0;
            sum += gameBoard[row][col];
        }
        if (flag == 1 && sum == 15)
            return 1;
    }
    if (gameBoard[0][0] && gameBoard[1][1] && gameBoard[2][2] && gameBoard[0][0] + gameBoard[1][1] + gameBoard[2][2] == 15)
        return 1;
    if (gameBoard[0][2] && gameBoard[1][1] && gameBoard[2][0] && gameBoard[0][2] + gameBoard[1][1] + gameBoard[2][0] == 15)
        return 1;
    return 0;
}
int isFull(int gameBoard[3][3])
{
    int row, col;
    for (row = 0; row < 3; row++)
        for (col = 0; col < 3; col++)
            if (gameBoard[row][col] == 0)
                return 0;
    return 1;
}
int slen(char c[])
{
    int i = 0, length = 0;
    for (i = 0; c[i] != '\0'; i++)
        length++;
    return length;
}
void convertCell(int position, int *r, int *c)
{
    int row = 0, column = 0;
    if (position == 1 || position == 4 || position == 7)
    {
        if (position == 4)
            row = 1;
        if (position == 1)
            row = 2;
    }
    if (position == 2 || position == 5 || position == 8)
    {
        column = 1;
        if (position == 5)
            row = 1;
        if (position == 2)
            row = 2;
    }
    if (position == 3 || position == 6 || position == 9)
    {
        column = 2;
        if (position == 6)
            row = 1;
        if (position == 3)
            row = 2;
    }
    *r = row;
    *c = column;
    return;
}
int checkValidity(int gameBoard[3][3], int numbers[9], int currentPlayer, int position, int number)
{
    // check if occupied
    int rw = 0, cn = 0;
    convertCell(position, &rw, &cn);
    if (gameBoard[rw][cn] != 0)
        return 0;
    // check if used
    if (numbers[number - 1] == 1)
        return 0;
    // check for player's number
    if (currentPlayer % 2 != number % 2)
        return 0;
    return 1;
}
void checkWinningMove(int gameBoard[3][3], int numbers[9], int *n, int *r, int *c, int currentPlayer)
{
    // check horizontal
    int i, j;
    int nr, nc, nub;
    int count = 0, sum = 0;
    for (i = 0; i < 3; i++)
    {
        count = sum = 0;
        for (j = 0; j < 3; j++)
        {
            sum += gameBoard[i][j];
            if (gameBoard[i][j] == 0)
            {
                nr = i;
                nc = j;
                count++;
            }
        }
        if (count == 1 && 15 - sum > 0 && 15 - sum <= 9 && (15 - sum) % 2 == currentPlayer % 2 && numbers[15 - sum - 1] == 0)
        {
            *r = nr;
            *c = nc;
            nub = 15 - sum;
            *n = nub;
            return;
        }
    }
    // check vertical
    for (i = 0; i < 3; i++)
    {
        count = sum = 0;
        for (j = 0; j < 3; j++)
        {
            sum += gameBoard[j][i];
            if (gameBoard[j][i] == 0)
            {
                nr = j;
                nc = i;
                count++;
            }
        }
        if (count == 1 && 15 - sum > 0 && 15 - sum <= 9 && (15 - sum) % 2 == currentPlayer % 2 && numbers[15 - sum - 1] == 0)
        {
            *r = nr;
            *c = nc;
            nub = 15 - sum;
            *n = nub;
            return;
        }
    }
    // check main diagonal
    count = sum = 0;
    for (i = 0; i < 3; i++)
    {
        sum += gameBoard[i][i];
        if (gameBoard[i][i] == 0)
        {
            nr = i;
            nc = i;
            count++;
        }
    }
    if (count == 1 && 15 - sum > 0 && 15 - sum <= 9 && (15 - sum) % 2 == currentPlayer % 2 && numbers[15 - sum - 1] == 0)
    {
        *r = nr;
        *c = nc;
        nub = 15 - sum;
        *n = nub;
        return;
    }
    // check secondary diagonal
    count = sum = 0;
    for (i = 0; i < 3; i++)
    {
        sum += gameBoard[2 - i][i];
        if (gameBoard[2 - i][i] == 0)
        {
            nr = 2 - i;
            nc = i;
            count++;
        }
    }
    if (count == 1 && 15 - sum > 0 && 15 - sum <= 9 && (15 - sum) % 2 == currentPlayer % 2 && numbers[15 - sum - 1] == 0)
    {
        *r = nr;
        *c = nc;
        nub = 15 - sum;
        *n = nub;
        return;
    }
    *n = 0;
    return;
}
void checkDefendMove(int gameBoard[3][3], int numbers[9], int *n, int *r, int *c, int currentPlayer)
{
    int i = 0, j = 0, k = 0;
    int nr = 0, nc = 0, nub = 0;
    int count = 0, sum = 0;
    // check horizontal
    for (i = 0; i < 3; i++)
    {
        count = sum = 0;
        for (j = 0; j < 3; j++)
        {
            sum += gameBoard[i][j];
            if (gameBoard[i][j] == 0)
            {
                nr = i;
                nc = j;
                count++;
            }
        }
        if (count == 1 && 15 - sum > 0 && 15 - sum <= 9 && (15 - sum) % 2 == 1 && numbers[15 - sum - 1] == 0)
        {
            for (k = 8; k >= 1; k -= 2)
            {
                if (numbers[k - 1])
                    continue;
                gameBoard[nr][nc] = k;
                numbers[k - 1] = 1;
                int ir, ic, neb = 0;
                checkWinningMove(gameBoard, numbers, &neb, &ir, &ic, 1);
                if (neb == 0)
                {
                    *r = nr;
                    *c = nc;
                    *n = k;
                    numbers[k - 1] = 0;
                    gameBoard[nr][nc] = 0;
                    return;
                }
                numbers[k - 1] = 0;
                gameBoard[nr][nc] = 0;
            }
        }
    }
    // check vertical
    for (i = 0; i < 3; i++)
    {
        count = sum = 0;
        for (j = 0; j < 3; j++)
        {
            sum += gameBoard[j][i];
            if (gameBoard[j][i] == 0)
            {
                nr = j;
                nc = i;
                count++;
            }
        }
        if (count == 1 && 15 - sum > 0 && 15 - sum <= 9 && (15 - sum) % 2 == 1 && numbers[15 - sum - 1] == 0)
        {
            for (k = 8; k >= 1; k -= 2)
            {
                if (numbers[k - 1])
                    continue;
                gameBoard[nr][nc] = k;
                numbers[k - 1] = 1;
                int ir, ic, neb = 0;
                checkWinningMove(gameBoard, numbers, &neb, &ir, &ic, 1);
                if (neb == 0)
                {
                    *r = nr;
                    *c = nc;
                    *n = k;
                    numbers[k - 1] = 0;
                    gameBoard[nr][nc] = 0;
                    return;
                }
                numbers[k - 1] = 0;
                gameBoard[nr][nc] = 0;
            }
        }
    }
    // check main diagonal
    count = sum = 0;
    for (i = 0; i < 3; i++)
    {
        sum += gameBoard[i][i];
        if (gameBoard[i][i] == 0)
        {
            nr = i;
            nc = i;
            count++;
        }
    }
    if (count == 1 && 15 - sum > 0 && 15 - sum <= 9 && (15 - sum) % 2 == 1 && numbers[15 - sum - 1] == 0)
    {
        for (k = 8; k >= 1; k -= 2)
        {
            if (numbers[k - 1])
                continue;
            gameBoard[nr][nc] = k;
            numbers[k - 1] = 1;
            int ir, ic, neb = 0;
            checkWinningMove(gameBoard, numbers, &neb, &ir, &ic, 1);
            if (neb == 0)
            {
                *r = nr;
                *c = nc;
                *n = k;
                numbers[k - 1] = 0;
                gameBoard[nr][nc] = 0;
                return;
            }
            numbers[k - 1] = 0;
            gameBoard[nr][nc] = 0;
        }
    }
    // check secondary diagonal
    count = sum = 0;
    for (i = 0; i < 3; i++)
    {
        sum += gameBoard[2 - i][i];
        if (gameBoard[2 - i][i] == 0)
        {
            nr = 2 - i;
            nc = i;
            count++;
        }
    }
    if (count == 1 && 15 - sum > 0 && 15 - sum <= 9 && (15 - sum) % 2 == 1 && numbers[15 - sum - 1] == 0)
    {
        for (k = 8; k >= 1; k -= 2)
        {
            if (numbers[k - 1])
                continue;
            gameBoard[nr][nc] = k;
            numbers[k - 1] = 1;
            int ir, ic, neb = 0;
            checkWinningMove(gameBoard, numbers, &neb, &ir, &ic, 1);
            if (neb == 0)
            {
                *r = nr;
                *c = nc;
                *n = k;
                numbers[k - 1] = 0;
                gameBoard[nr][nc] = 0;
                return;
            }
            numbers[k - 1] = 0;
            gameBoard[nr][nc] = 0;
        }
    }
    return;
}
void checkPossibleMove(int gameBoard[3][3], int numbers[9], int *n, int *r, int *c, int flag)
{
    int i = 0, j = 0, k = 0;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (gameBoard[i][j])
                continue;
            for (k = 8; k >= 2; k -= 2)
            {
                if (numbers[k - 1])
                    continue;
                gameBoard[i][j] = k;
                int nn = 0, rr = 0, cc = 0;
                if (flag == 1)
                {
                    checkWinningMove(gameBoard, numbers, &nn, &rr, &cc, 1);
                    if (nn == 0)
                    {
                        *n = k;
                        *r = i;
                        *c = j;
                        gameBoard[i][j] = k;
                        return;
                    }
                }
                else
                {
                    *n = k;
                    *r = i;
                    *c = j;
                    gameBoard[i][j] = k;
                    return;
                }
                gameBoard[i][j] = k;
            }
        }
    }
    return;
}
typedef struct AP
{
    int row, col, number, score;
} AP;
AP minimax(int gameBoard[3][3], int numbers[9], int currentPlayer, int depth, int alpha, int beta)
{
    int bs = (currentPlayer % 2) ? 10000000 : -10000000;
    AP best = (AP){-1, -1, -1, bs};
    if (isFull(gameBoard) || hasWinner(gameBoard))
    {
        if (hasWinner(gameBoard))
            bs = (currentPlayer % 2) ? 10000000 : -10000000;
        else
            bs = 0;
        best.score = bs;
        return best;
    }
    int i, j, k, sign = 0;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (gameBoard[i][j])
                continue;
            for (k = 1; k <= 9; k++)
            {
                if (((k % 2) != (currentPlayer % 2)) || numbers[k - 1])
                    continue;
                AP currentMove = (AP){i, j, k, -1};
                gameBoard[i][j] = k;
                numbers[k - 1] = 1;
                if (currentPlayer == 2)
                {
                    int score = minimax(gameBoard, numbers, 1, depth + 1, alpha, beta).score;
                    if (best.score < score - depth * 10)
                    {
                        currentMove.score = score - depth * 10;
                        best = currentMove;
                        alpha = alpha < best.score ? best.score : alpha;
                        gameBoard[best.row][best.col] = 0;
                        numbers[k - 1] = 0;
                        if (beta <= alpha)
                        {
                            sign = 1;
                            break;
                        }
                    }
                }
                else
                {
                    int score = minimax(gameBoard, numbers, 2, depth + 1, alpha, beta).score;
                    if (best.score > score + depth * 10)
                    {
                        currentMove.score = score + depth * 10;
                        best = currentMove;
                        beta = beta > best.score ? best.score : beta;
                        gameBoard[best.row][best.col] = 0;
                        numbers[k - 1] = 0;
                        if (beta <= alpha)
                        {
                            sign = 1;
                            break;
                        }
                    }
                }
                numbers[k - 1] = 0;
                gameBoard[i][j] = 0;
            }
            if (sign == 1)
                break;
        }
        if (sign == 1)
            break;
    }
    return best;
}
void AImove(int gameBoard[3][3], int numbers[9], int *n, int *r, int *c, int mode)
{
    if (mode == 1)
    {
        // 1. Winning Move
        checkWinningMove(gameBoard, numbers, n, r, c, 2);
        if (*n)
            return;
        // 2. Defending Move
        checkDefendMove(gameBoard, numbers, n, r, c, 2);
        if (*n)
            return;
        // 3. A Move Without Immediate Losing
        checkPossibleMove(gameBoard, numbers, n, r, c, 1);
        if (*n)
            return;
        // 4. Worst Case: Hope the user won't find the way and make a mistake
        checkPossibleMove(gameBoard, numbers, n, r, c, 0);
    }
    else
    {
        checkWinningMove(gameBoard, numbers, n, r, c, 2);
        if (*n)
            return;
        int best_moverow = -1, best_movecol = -1, best_score = -10000000;
        AP tmp = minimax(gameBoard, numbers, 2, 0, -10000000, 10000000);
        *n = tmp.number;
        *r = tmp.row;
        *c = tmp.col;
    }
    return;
}
void placeNumber(int gameBoard[3][3], int numbers[9], int currentPlayer)
{
    int mode = currentPlayer % 10;      // find AI mode
    currentPlayer = currentPlayer / 10; // find currentPlayer
    if (currentPlayer == 1)
    {
        printf("### Player 1's turn ###\n");
        int position = 0, number = 0;
        while (1)
        {
            char buffer[1011];
            int i = 0;
            while (1)
            {
                printf("Input the position: ");
                fgets(buffer, 1010, stdin);
                for (i = slen(buffer) - 1; i >= 0; i--)
                {
                    if (isspace(buffer[i]))
                        buffer[i] = '\0';
                }
                if (slen(buffer) == 1 && '1' <= buffer[0] && buffer[0] <= '9')
                {
                    position = buffer[0] - '0';
                    break;
                }
                else
                    printf("Invalid input format!\n");
            }
            while (1)
            {
                printf("Input the number: ");
                fgets(buffer, 1010, stdin);
                for (i = slen(buffer) - 1; i >= 0; i--)
                {
                    if (isspace(buffer[i]))
                        buffer[i] = '\0';
                }
                if (slen(buffer) == 1 && '1' <= buffer[0] && buffer[0] <= '9')
                {
                    number = buffer[0] - '0';
                    break;
                }
                else
                    printf("Invalid input format!\n");
            }
            printf("Checking for validity...\n");
            if (checkValidity(gameBoard, numbers, currentPlayer, position, number))
            {
                while (1)
                {
                    printf("You have input position = %d, number = %d, please confirm. [Y/n]\n", position, number);
                    fgets(buffer, 1010, stdin);
                    for (i = slen(buffer) - 1; i >= 0; i--)
                    {
                        if (isspace(buffer[i]))
                            buffer[i] = '\0';
                    }
                    if (slen(buffer) == 1 && (buffer[0] == 'Y' || buffer[0] == 'y' || buffer[0] == 'N' || buffer[0] == 'n'))
                        break;
                    else
                        printf("Invalid input format!\n");
                }
                if (buffer[0] == 'Y' || buffer[0] == 'y')
                    break;
                else
                    printf("Input again!\n");
            }
            else
                printf("Sorry, your input does not satisfy the game rule.\n");
        }
        int rw = 0, cn = 0;
        convertCell(position, &rw, &cn);
        gameBoard[rw][cn] = number;
        numbers[number - 1] = 1;
    }
    else
    {
        printf("### Player 2's turn ###\n");
        int rw = 0, cn = 0, nb = 0;
        AImove(gameBoard, numbers, &nb, &rw, &cn, mode);
        gameBoard[rw][cn] = nb;
        numbers[nb - 1] = 1;
        printf("AI placed number %d at position: row = %d, column = %d\n", nb, rw, cn);
    }
    return;
}
int main()
{
    int gameBoard[3][3] = {0};
    int numbers[9] = {0};
    int currentPlayer;
    int gameContinue;
    int mode;
    currentPlayer = 1;
    gameContinue = 1;
    mode = 0;
    char buffer[1010];
    int i;
    while (1)
    {
        printf("Input the mode: \n1 for Naive Mode\n2 for Alpha-Beta Search\n");
        fgets(buffer, 1010, stdin);
        for (i = slen(buffer) - 1; i >= 0; i--)
        {
            if (isspace(buffer[i]))
                buffer[i] = '\0';
        }
        if (slen(buffer) == 1 && '1' <= buffer[0] && buffer[0] <= '2')
        {
            mode = buffer[0] - '0';
            break;
        }
        else
            printf("Invalid input format!\n");
    }
    while (1)
    {
        printInfo(gameBoard, numbers);
        placeNumber(gameBoard, numbers, currentPlayer * 10 + mode);
        if (hasWinner(gameBoard) == 1)
        {
            printInfo(gameBoard, numbers);
            printf("Congratulations! Player %d wins!\n", currentPlayer);
            break;
        }
        else if (isFull(gameBoard) == 1)
        {
            printInfo(gameBoard, numbers);
            printf("Draw game.\n");
            break;
        }
        if (currentPlayer == 1)
            currentPlayer = 2;
        else
            currentPlayer = 1;
    }
    return 0;
}