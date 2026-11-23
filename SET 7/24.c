#include <stdio.h>

#define V 5
#define M 3

int graph[V][V] = {
    {0, 1, 1, 1, 0},
    {1, 0, 1, 0, 1},
    {1, 1, 0, 1, 1},
    {1, 0, 1, 0, 1},
    {0, 1, 1, 1, 0}
};

int color[V];

int isSafe(int vertex, int c) {
    for (int i = 0; i < V; i++) {
        if (graph[vertex][i] && color[i] == c)
            return 0;
    }

    return 1;
}

int graphColoring(int vertex) {
    if (vertex == V)
        return 1;

    for (int c = 1; c <= M; c++) {
        if (isSafe(vertex, c)) {
            color[vertex] = c;

            if (graphColoring(vertex + 1))
                return 1;

            color[vertex] = 0;
        }
    }

    return 0;
}

int main() {
    if (graphColoring(0)) {
        printf("Color assignment:\n");

        for (int i = 0; i < V; i++)
            printf("Vertex %d -> Color %d\n", i, color[i]);
    }
    else {
        printf("Coloring not possible\n");
    }

    return 0;
}