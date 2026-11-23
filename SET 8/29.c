#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int path[MAX];
int visited[MAX];
int n, e;

int isSafe(int vertex, int pos) {
    if (!graph[path[pos - 1]][vertex])
        return 0;

    if (visited[vertex])
        return 0;

    return 1;
}

int hamiltonian(int pos) {
    if (pos == n) {
        return graph[path[n - 1]][path[0]];
    }

    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;
            visited[v] = 1;

            if (hamiltonian(pos + 1))
                return 1;

            visited[v] = 0;
        }
    }

    return 0;
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter edges:\n");

    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    path[0] = 0;
    visited[0] = 1;

    if (hamiltonian(1)) {
        printf("Hamiltonian Cycle exists:\n");

        for (int i = 0; i < n; i++)
            printf("%d -> ", path[i]);

        printf("%d\n", path[0]);
    }
    else {
        printf("Hamiltonian Cycle does not exist\n");
    }

    return 0;
}