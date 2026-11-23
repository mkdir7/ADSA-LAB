#include <stdio.h>

#define N 4
#define W 7

int max(int a, int b) {
    return a > b ? a : b;
}

int knapsack(int weight[], int value[]) {
    int dp[N + 1][W + 1];

    for (int i = 0; i <= N; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            }
            else if (weight[i - 1] <= w) {
                dp[i][w] = max(
                    value[i - 1] + dp[i - 1][w - weight[i - 1]],
                    dp[i - 1][w]
                );
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[N][W];
}

int main() {
    int weight[N] = {1, 3, 4, 5};
    int value[N] = {1, 4, 5, 7};

    printf("Maximum value = %d\n", knapsack(weight, value));

    return 0;
}