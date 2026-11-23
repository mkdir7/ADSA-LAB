#include <stdio.h>

#define V 6

int graph[V][V] = {
    {0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0}
};

int visited[V];
int recursionStack[V];
int order[V];
int top = -1;

int DFS(int u) {
    visited[u] = 1;
    recursionStack[u] = 1;

    for (int v = 0; v < V; v++) {
        if (!graph[u][v])
            continue;

        if (!visited[v]) {
            if (!DFS(v))
                return 0;
        }
        else if (recursionStack[v]) {
            return 0;
        }
    }

    recursionStack[u] = 0;
    order[++top] = u;

    return 1;
}

void topologicalSort() {
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
        recursionStack[i] = 0;
    }

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (!DFS(i)) {
                printf("Topological sorting not possible\n");
                return;
            }
        }
    }

    printf("Topological Order: ");

    for (int i = top; i >= 0; i--)
        printf("%d ", order[i]);

    printf("\n");
}

int main() {
    topologicalSort();

    return 0;
}