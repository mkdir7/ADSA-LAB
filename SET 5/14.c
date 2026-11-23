#include <stdio.h>

#define V 6

int graph[V][V];
int color[V];
int discover[V];
int finish[V];
int time = 0;

void DFSVisit(int u) {
    color[u] = 1;
    discover[u] = ++time;

    for (int v = 0; v < V; v++) {
        if (!graph[u][v])
            continue;

        if (color[v] == 0) {
            printf("%d -> %d : Tree Edge\n", u, v);
            DFSVisit(v);
        }
        else if (color[v] == 1) {
            printf("%d -> %d : Back Edge\n", u, v);
        }
        else {
            if (discover[u] < discover[v])
                printf("%d -> %d : Forward Edge\n", u, v);
            else
                printf("%d -> %d : Cross Edge\n", u, v);
        }
    }

    color[u] = 2;
    finish[u] = ++time;
}

void DFS() {
    for (int i = 0; i < V; i++)
        color[i] = 0;

    time = 0;

    for (int i = 0; i < V; i++) {
        if (color[i] == 0)
            DFSVisit(i);
    }
}

int main() {
    graph[0][1] = 1;
    graph[0][2] = 1;
    graph[1][2] = 1;
    graph[1][3] = 1;
    graph[2][0] = 1;
    graph[2][3] = 1;
    graph[3][4] = 1;
    graph[4][5] = 1;
    graph[5][3] = 1;

    DFS();

    return 0;
}