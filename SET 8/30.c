#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int color[MAX];
int queue[MAX];
int n, e;

int isBipartite() {
    for (int i = 0; i < n; i++)
        color[i] = -1;

    for (int start = 0; start < n; start++) {
        if (color[start] != -1)
            continue;

        int front = 0;
        int rear = 0;

        queue[rear++] = start;
        color[start] = 0;

        while (front < rear) {
            int u = queue[front++];

            for (int v = 0; v < n; v++) {
                if (!graph[u][v])
                    continue;

                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    queue[rear++] = v;
                }
                else if (color[v] == color[u]) {
                    return 0;
                }
            }
        }
    }

    return 1;
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

    if (isBipartite()) {
        printf("Graph is bipartite\n");

        printf("Set 1: ");

        for (int i = 0; i < n; i++) {
            if (color[i] == 0)
                printf("%d ", i);
        }

        printf("\nSet 2: ");

        for (int i = 0; i < n; i++) {
            if (color[i] == 1)
                printf("%d ", i);
        }

        printf("\n");
    }
    else {
        printf("Graph is not bipartite\n");
    }

    return 0;
}