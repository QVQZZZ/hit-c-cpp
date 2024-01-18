#include <stdio.h>
#include <stdbool.h>

#define N 8

static int countOfSolutions = 0;

void printSolution(int board[N][N]) {
    printf("solution%d:\n", countOfSolutions + 1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
}

bool check(int board[N][N], int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) {
            return false;
        }
    }

    for (int j = 0; j < col; j++) {
        if (board[row][j] == 1) {
            return false;
        }
    }

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

bool solveNQueens(int board[N][N], int row) {
    if (row == N) {
        printSolution(board);
        countOfSolutions++;
        return true;
    }

    bool res = false;
    for (int col = 0; col < N; col++) {
        if (check(board, row, col)) {
            board[row][col] = 1;
            res = solveNQueens(board, row + 1) || res;
            board[row][col] = 0;
        }
    }

    return res;
}

int main() {
    int board[N][N] = {0};
    if (!solveNQueens(board, 0)) {
        printf("no solution.\n");
    }
    printf("\ncount of solutions: %d.\n", countOfSolutions);
    return 0;
}
