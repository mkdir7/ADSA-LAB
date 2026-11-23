#include <stdio.h>
#include <stdlib.h>

#define N 4
#define MAX_NODES 100000

typedef struct Node {
    int board[N][N];
    int x, y;
    int level;
    int cost;
    struct Node *parent;
} Node;

Node *queue[MAX_NODES];
int size = 0;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int goal[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};

int calculateCost(int board[N][N]) {
    int cost = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] != 0) {
                int value = board[i][j] - 1;
                int goalX = value / N;
                int goalY = value % N;

                cost += abs(i - goalX) + abs(j - goalY);
            }
        }
    }

    return cost;
}

Node *createNode(int board[N][N], int x, int y, int newX, int newY, int level, Node *parent) {
    Node *node = (Node *)malloc(sizeof(Node));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            node->board[i][j] = board[i][j];

    node->board[x][y] = node->board[newX][newY];
    node->board[newX][newY] = 0;

    node->x = newX;
    node->y = newY;
    node->level = level;
    node->cost = level + calculateCost(node->board);
    node->parent = parent;

    return node;
}

void push(Node *node) {
    if (size >= MAX_NODES)
        return;

    queue[size++] = node;
}

Node *pop() {
    int minIndex = 0;

    for (int i = 1; i < size; i++) {
        if (queue[i]->cost < queue[minIndex]->cost)
            minIndex = i;
    }

    Node *node = queue[minIndex];

    for (int i = minIndex; i < size - 1; i++)
        queue[i] = queue[i + 1];

    size--;

    return node;
}

int isGoal(int board[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] != goal[i][j])
                return 0;

    return 1;
}

void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0)
                printf("   ");
            else
                printf("%2d ", board[i][j]);
        }
        printf("\n");
    }

    printf("\n");
}

void printPath(Node *node) {
    if (node == NULL)
        return;

    printPath(node->parent);
    printBoard(node->board);
}

void solve(int initial[N][N], int x, int y) {
    Node *root = (Node *)malloc(sizeof(Node));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            root->board[i][j] = initial[i][j];

    root->x = x;
    root->y = y;
    root->level = 0;
    root->cost = calculateCost(root->board);
    root->parent = NULL;

    push(root);

    while (size > 0) {
        Node *current = pop();

        if (isGoal(current->board)) {
            printPath(current);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int newX = current->x + dx[i];
            int newY = current->y + dy[i];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                Node *child = createNode(
                    current->board,
                    current->x,
                    current->y,
                    newX,
                    newY,
                    current->level + 1,
                    current
                );

                push(child);
            }
        }
    }

    printf("No solution found\n");
}

int main() {
    int initial[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 0, 15}
    };

    solve(initial, 3, 2);

    return 0;
}