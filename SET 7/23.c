#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char id;
    int deadline;
    int profit;
} Job;

int compare(const void *a, const void *b) {
    Job *x = (Job *)a;
    Job *y = (Job *)b;

    return y->profit - x->profit;
}

void jobSequencing(Job jobs[], int n) {
    qsort(jobs, n, sizeof(Job), compare);

    int maxDeadline = 0;

    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }

    char slot[maxDeadline + 1];

    for (int i = 0; i <= maxDeadline; i++)
        slot[i] = '-';

    int totalProfit = 0;

    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline; j >= 1; j--) {
            if (slot[j] == '-') {
                slot[j] = jobs[i].id;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    printf("Job Sequence: ");

    for (int i = 1; i <= maxDeadline; i++) {
        if (slot[i] != '-')
            printf("%c ", slot[i]);
    }

    printf("\nMaximum Profit = %d\n", totalProfit);
}

int main() {
    Job jobs[] = {
        {'A', 2, 100},
        {'B', 1, 19},
        {'C', 2, 27},
        {'D', 1, 25},
        {'E', 3, 15}
    };

    int n = sizeof(jobs) / sizeof(jobs[0]);

    jobSequencing(jobs, n);

    return 0;
}