#include <stdio.h>

#define V 6

int graph[V][V];
int visited[V];
int path[V];

int minCycle = 99999;
int maxCycle = 0;

void DFS(int start, int current, int depth, int directed) {
    visited[current] = 1;
    path[depth] = current;

    for (int next = 0; next < V; next++) {
        if (!graph[current][next])
            continue;

        if (next == start && depth >= 2) {
            int length = depth + 1;

            if (length < minCycle)
                minCycle = length;

            if (length > maxCycle)
                maxCycle = length;
        }
        else if (!visited[next]) {
            DFS(start, next, depth + 1, directed);
        }
    }

    visited[current] = 0;
}

void findCycles(int directed) {
    minCycle = 99999;
    maxCycle = 0;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            visited[j] = 0;

        DFS(i, i, 0, directed);
    }

    if (maxCycle == 0) {
        printf("No cycle exists\n");
    } else {
        printf("Smallest cycle: %d\n", minCycle);
        printf("Largest cycle: %d\n", maxCycle);
    }
}

int main() {
    graph[0][1] = 1;
    graph[1][2] = 1;
    graph[2][0] = 1;
    graph[2][3] = 1;
    graph[3][4] = 1;
    graph[4][5] = 1;
    graph[5][3] = 1;

    findCycles(1);

    return 0;
}