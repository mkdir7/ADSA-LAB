#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX_N 100
#define INF 1000000000

int graph[MAX_N][MAX_N];
int visited[MAX_N];
int n;
int bestCost;

void tsp(int current, int count, int cost) {
    if (cost >= bestCost)
        return;

    if (count == n) {
        if (graph[current][0] > 0 &&
            cost + graph[current][0] < bestCost) {
            bestCost = cost + graph[current][0];
        }
        return;
    }

    for (int next = 1; next < n; next++) {
        if (!visited[next] && graph[current][next] > 0) {
            visited[next] = 1;

            tsp(next,
                count + 1,
                cost + graph[current][next]);

            visited[next] = 0;
        }
    }
}

void generateGraph() {
    srand(1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = rand() % 100 + 1;
        }
    }
}

void solveTSP() {
    bestCost = INF;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    visited[0] = 1;

    tsp(0, 1, 0);
}

int main() {
    int sizes[] = {10, 20, 40, 60, 100};
    int count = 5;

    printf("Nodes\tExecution Time (seconds)\tBest Cost\n");

    for (int i = 0; i < count; i++) {
        n = sizes[i];

        if (n > 20) {
            printf("%d\tNot practical for exact TSP\t-\n", n);
            continue;
        }

        generateGraph();

        clock_t start = clock();

        solveTSP();

        clock_t end = clock();

        double timeTaken =
            (double)(end - start) / CLOCKS_PER_SEC;

        printf("%d\t%f\t\t%d\n",
               n, timeTaken, bestCost);
    }

    return 0;
}