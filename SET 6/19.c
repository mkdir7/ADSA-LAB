#include <stdio.h>

#define N 4
#define W 7

int weight[N] = {1, 3, 4, 5};
int value[N] = {1, 4, 5, 7};

int maxValue = 0;

void knapsack(int index, int currentWeight, int currentValue) {
    if (index == N) {
        if (currentValue > maxValue)
            maxValue = currentValue;
        return;
    }

    if (currentWeight + weight[index] <= W)
        knapsack(
            index + 1,
            currentWeight + weight[index],
            currentValue + value[index]
        );

    knapsack(index + 1, currentWeight, currentValue);
}

int main() {
    knapsack(0, 0, 0);

    printf("Maximum value = %d\n", maxValue);

    return 0;
}