#include <stdio.h>

void coinChange(int coins[], int n, int amount) {
    int count = 0;

    printf("Coins used: ");

    for (int i = 0; i < n; i++) {
        while (amount >= coins[i]) {
            amount -= coins[i];
            printf("%d ", coins[i]);
            count++;
        }
    }

    printf("\nNumber of coins = %d\n", count);

    if (amount != 0)
        printf("Exact change not possible\n");
}

int main() {
    int coins[] = {10, 5, 2, 1};
    int n = 4;
    int amount = 57;

    coinChange(coins, n, amount);

    return 0;
}