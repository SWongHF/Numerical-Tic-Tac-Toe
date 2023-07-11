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
                int ir = 0, ic = 0, neb = 0;
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
                int ir = 0, ic = 0, neb = 0;
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
            int ir = 0, ic = 0, neb = 0;
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
            int ir = 0, ic = 0, neb = 0;
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
                        gameBoard[i][j] = 0;
                        return;
                    }
                }
                else
                {
                    *n = k;
                    *r = i;
                    *c = j;
                    gameBoard[i][j] = 0;
                    return;
                }
                gameBoard[i][j] = 0;
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
                        gameBoard[i][j] = 0;
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
                        gameBoard[i][j] = 0;
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
        checkWinningMove(gameBoard, numbers, n, r, c, 2);
        if (*n)
            return;
        checkDefendMove(gameBoard, numbers, n, r, c, 2);
        if (*n)
            return;
        checkPossibleMove(gameBoard, numbers, n, r, c, 1);
        if (*n)
            return;
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
long long win, lose, rounds, mode;
void dfs(int gameBoard[3][3], int numbers[9], int depth)
{
    if (hasWinner(gameBoard) || isFull(gameBoard))
    {
        rounds++;
        if (hasWinner(gameBoard) && depth % 2 == 0)
            lose++;
        if (hasWinner(gameBoard) && depth % 2 == 1)
            win++;
        printInfo(gameBoard, numbers);
        return;
    }
    if (depth % 2 == 1)
    {
        int rw = 0, cn = 0;
        int i, j, k;
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                if (gameBoard[i][j] != 0)
                    continue;
                for (k = 1; k <= 9; k += 2)
                {
                    if (numbers[k - 1])
                        continue;
                    gameBoard[i][j] = k;
                    numbers[k - 1] = 1;
                    dfs(gameBoard, numbers, depth + 1);
                    gameBoard[i][j] = 0;
                    numbers[k - 1] = 0;
                }
            }
        }
    }
    else
    {
        int rw = 0, cn = 0, nb = 0;
        AImove(gameBoard, numbers, &nb, &rw, &cn, mode);
        gameBoard[rw][cn] = nb;
        numbers[nb - 1] = 1;
        int rrr = rw, ccc = cn, nnn = nb;
        dfs(gameBoard, numbers, depth + 1);
        gameBoard[rrr][ccc] = 0;
        numbers[nnn - 1] = 0;
    }
}
void game()
{
    int gameBoard[3][3] = {0};
    int numbers[9] = {0};
    mode = 2;
    int i;
    dfs(gameBoard, numbers, 1);
    return;
}
int main()
{
    game();
    printf("%d games\n", rounds);
    printf("winning rate = %.4lf, losing rate = %.4lf\n", (double)win / rounds, (double)lose / rounds);
    return 0;
}