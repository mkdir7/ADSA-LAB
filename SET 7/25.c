#include <stdio.h>

#define V 7

int graph[V][V];

int disc[V], low[V], visited[V], parent[V];
int time = 0;

int stack[V];
int top = -1;

void SCCUtil(int u) {
    disc[u] = low[u] = ++time;
    stack[++top] = u;
    visited[u] = 1;

    for (int v = 0; v < V; v++) {
        if (!graph[u][v])
            continue;

        if (!disc[v]) {
            SCCUtil(v);

            if (low[v] < low[u])
                low[u] = low[v];
        }
        else if (visited[v]) {
            if (disc[v] < low[u])
                low[u] = disc[v];
        }
    }

    if (low[u] == disc[u]) {
        printf("SCC: ");

        while (1) {
            int v = stack[top--];
            visited[v] = 0;
            printf("%d ", v);

            if (v == u)
                break;
        }

        printf("\n");
    }
}

void findSCC() {
    for (int i = 0; i < V; i++) {
        disc[i] = 0;
        low[i] = 0;
        visited[i] = 0;
    }

    time = 0;
    top = -1;

    printf("Strongly Connected Components:\n");

    for (int i = 0; i < V; i++) {
        if (!disc[i])
            SCCUtil(i);
    }
}

void BCCUtil(int u) {
    disc[u] = low[u] = ++time;

    int children = 0;

    for (int v = 0; v < V; v++) {
        if (!graph[u][v])
            continue;

        if (!disc[v]) {
            children++;
            parent[v] = u;

            printf("Edge %d-%d ", u, v);

            BCCUtil(v);

            if (low[v] < low[u])
                low[u] = low[v];

            if ((parent[u] == -1 && children > 1) ||
                (parent[u] != -1 && low[v] >= disc[u])) {
                printf("\nBiconnected component at %d: ", u);
            }

            if (low[v] > disc[u])
                printf("\nBridge: %d - %d\n", u, v);
        }
        else if (v != parent[u] && disc[v] < disc[u]) {
            if (disc[v] < low[u])
                low[u] = disc[v];

            printf("Edge %d-%d ", u, v);
        }
    }
}

void findBCC() {
    for (int i = 0; i < V; i++) {
        disc[i] = 0;
        low[i] = 0;
        parent[i] = -1;
    }

    time = 0;

    printf("\nBiconnected Components, Articulation Points and Bridges:\n");

    for (int i = 0; i < V; i++) {
        if (!disc[i])
            BCCUtil(i);
    }

    printf("\nArticulation Points:\n");

    for (int u = 0; u < V; u++) {
        int children = 0;
        int articulation = 0;

        for (int v = 0; v < V; v++) {
            if (parent[v] == u)
                children++;
        }

        if (parent[u] == -1) {
            if (children > 1)
                articulation = 1;
        }
        else {
            for (int v = 0; v < V; v++) {
                if (parent[v] == u && low[v] >= disc[u])
                    articulation = 1;
            }
        }

        if (articulation)
            printf("%d ", u);
    }

    printf("\n");
}

int main() {
    graph[0][1] = graph[1][0] = 1;
    graph[1][2] = graph[2][1] = 1;
    graph[2][0] = graph[0][2] = 1;
    graph[1][3] = graph[3][1] = 1;
    graph[3][4] = graph[4][3] = 1;
    graph[4][5] = graph[5][4] = 1;
    graph[5][3] = graph[3][5] = 1;
    graph[4][6] = graph[6][4] = 1;

    findSCC();
    findBCC();

    return 0;
}