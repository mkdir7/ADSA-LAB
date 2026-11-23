#include <stdio.h>
#include <stdlib.h>

#define V 5
#define E 7

typedef struct {
    int src;
    int dest;
    int weight;
} Edge;

int parent[V];

int find(int i) {
    if (parent[i] == i)
        return i;

    return parent[i] = find(parent[i]);
}

void unionSet(int a, int b) {
    int x = find(a);
    int y = find(b);

    parent[x] = y;
}

int compare(const void *a, const void *b) {
    Edge *x = (Edge *)a;
    Edge *y = (Edge *)b;

    return x->weight - y->weight;
}

void kruskal(Edge edges[]) {
    qsort(edges, E, sizeof(Edge), compare);

    for (int i = 0; i < V; i++)
        parent[i] = i;

    printf("Edge\tWeight\n");

    int count = 0;
    int i = 0;

    while (count < V - 1 && i < E) {
        Edge edge = edges[i++];

        int x = find(edge.src);
        int y = find(edge.dest);

        if (x != y) {
            printf("%d - %d\t%d\n",
                   edge.src, edge.dest, edge.weight);

            unionSet(x, y);
            count++;
        }
    }
}

int main() {
    Edge edges[E] = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };

    kruskal(edges);

    return 0;
}