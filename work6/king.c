#include <stdio.h>
#include <stdbool.h>

#define N 4

static int countOfSolutions = 0;

void printSolution(int board[N][N]) {
    printf("\nsolution%d:\n", countOfSolutions + 1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
}

bool check(int board[N][N], int row, int col) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < N && newCol >= 0 && newCol < N) {
                if (board[newRow][newCol] == 1) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool solveNKings(int board[N][N], int kingsLeft, int row, int col) {
    if (kingsLeft == 0) {
        printSolution(board);
        countOfSolutions++;
        return true;
    }

    bool res = false;
    for (int r = row; r < N; r++) {
        for (int c = (r == row) ? col : 0; c < N; c++) { // 不能直接 c = col, 因为 r!=row 的时候代表换行, c 要变成 0
            if (check(board, r, c)) {
                board[r][c] = 1;
                if (c + 1 == N) {
                    res = solveNKings(board, kingsLeft - 1, r + 1, 0) || res;
                } else {
                    res = solveNKings(board, kingsLeft - 1, r, c + 1) || res;
                }
                board[r][c] = 0;
            }
        }
    }

    return res;
}

int main() {
    int board[N][N] = {0};
    if (!solveNKings(board, 4, 0, 0)) {
        printf("no solution.\n");
    }
    printf("\ncount of solutions: %d.\n", countOfSolutions);
    return 0;
}
