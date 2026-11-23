#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int clique[MAX];
int n, e, m;

int isSafe(int vertex, int pos) {
    for (int i = 0; i < pos; i++) {
        if (!graph[clique[i]][vertex])
            return 0;
    }

    return 1;
}

int findClique(int pos, int start) {
    if (pos == m)
        return 1;

    for (int v = start; v < n; v++) {
        if (isSafe(v, pos)) {
            clique[pos] = v;

            if (findClique(pos + 1, v + 1))
                return 1;
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

    printf("Enter clique size m: ");
    scanf("%d", &m);

    if (m > n || m <= 0) {
        printf("Invalid value of m\n");
        return 0;
    }

    if (findClique(0, 0)) {
        printf("Clique of size %d exists:\n", m);

        for (int i = 0; i < m; i++)
            printf("%d ", clique[i]);

        printf("\n");
    }
    else {
        printf("Clique of size %d does not exist\n", m);
    }

    return 0;
}