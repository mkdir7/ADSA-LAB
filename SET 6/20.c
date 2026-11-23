#include <stdio.h>
#include <stdlib.h>

#define N 8

int board[N][N];

int isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i][col])
            return 0;
    }

    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j])
            return 0;
    }

    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) {
        if (board[i][j])
            return 0;
    }

    return 1;
}

int solveNQueens(int row) {
    if (row == N)
        return 1;

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;

            if (solveNQueens(row + 1))
                return 1;

            board[row][col] = 0;
        }
    }

    return 0;
}

void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j])
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
}

int main() {
    if (solveNQueens(0))
        printBoard();
    else
        printf("No solution exists\n");

    return 0;
}