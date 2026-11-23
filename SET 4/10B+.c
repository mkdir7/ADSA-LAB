#include <stdio.h>
#include <stdlib.h>

#define ORDER 4

typedef struct BPlusNode {
    int key[ORDER];
    struct BPlusNode *child[ORDER + 1];
    struct BPlusNode *next;
    int n;
    int leaf;
} BPlusNode;

BPlusNode *createNode(int leaf) {
    BPlusNode *node = (BPlusNode *)malloc(sizeof(BPlusNode));

    node->n = 0;
    node->leaf = leaf;
    node->next = NULL;

    for (int i = 0; i <= ORDER; i++)
        node->child[i] = NULL;

    return node;
}

BPlusNode *createTree() {
    return createNode(1);
}

BPlusNode *searchItem(BPlusNode *root, int key) {
    if (root == NULL)
        return NULL;

    if (root->leaf) {
        for (int i = 0; i < root->n; i++) {
            if (root->key[i] == key)
                return root;
        }

        return NULL;
    }

    int i = 0;

    while (i < root->n && key >= root->key[i])
        i++;

    return searchItem(root->child[i], key);
}

void insertLeaf(BPlusNode *root, int key) {
    int i = root->n - 1;

    while (i >= 0 && key < root->key[i]) {
        root->key[i + 1] = root->key[i];
        i--;
    }

    root->key[i + 1] = key;
    root->n++;
}

void insertItem(BPlusNode **root, int key) {
    if (searchItem(*root, key) != NULL)
        return;

    if ((*root)->leaf && (*root)->n < ORDER) {
        insertLeaf(*root, key);
        return;
    }

    if ((*root)->leaf) {
        BPlusNode *left = *root;
        BPlusNode *right = createNode(1);

        int temp[ORDER + 1];

        for (int i = 0; i < ORDER; i++)
            temp[i] = left->key[i];

        int pos = 0;

        while (pos < ORDER && temp[pos] < key)
            pos++;

        for (int i = ORDER; i > pos; i--)
            temp[i] = temp[i - 1];

        temp[pos] = key;

        left->n = 0;

        for (int i = 0; i < (ORDER + 1) / 2; i++)
            left->key[left->n++] = temp[i];

        for (int i = (ORDER + 1) / 2; i < ORDER + 1; i++)
            right->key[right->n++] = temp[i];

        left->next = right;

        BPlusNode *newRoot = createNode(0);

        newRoot->n = 1;
        newRoot->key[0] = right->key[0];
        newRoot->child[0] = left;
        newRoot->child[1] = right;

        *root = newRoot;
        return;
    }

    int i = 0;

    while (i < (*root)->n && key >= (*root)->key[i])
        i++;

    BPlusNode *child = (*root)->child[i];

    if (child->n < ORDER) {
        insertLeaf(child, key);
        return;
    }

    BPlusNode *right = createNode(1);

    int temp[ORDER + 1];

    for (int j = 0; j < ORDER; j++)
        temp[j] = child->key[j];

    int pos = 0;

    while (pos < ORDER && temp[pos] < key)
        pos++;

    for (int j = ORDER; j > pos; j--)
        temp[j] = temp[j - 1];

    temp[pos] = key;

    child->n = 0;

    for (int j = 0; j < (ORDER + 1) / 2; j++)
        child->key[child->n++] = temp[j];

    for (int j = (ORDER + 1) / 2; j < ORDER + 1; j++)
        right->key[right->n++] = temp[j];

    right->next = child->next;
    child->next = right;

    for (int j = (*root)->n; j > i; j--) {
        (*root)->key[j] = (*root)->key[j - 1];
        (*root)->child[j + 1] = (*root)->child[j];
    }

    (*root)->key[i] = right->key[0];
    (*root)->child[i + 1] = right;
    (*root)->n++;
}

void deleteItem(BPlusNode **root, int key) {
    BPlusNode *node = searchItem(*root, key);

    if (node == NULL)
        return;

    int pos = -1;

    for (int i = 0; i < node->n; i++) {
        if (node->key[i] == key) {
            pos = i;
            break;
        }
    }

    if (pos == -1)
        return;

    for (int i = pos; i < node->n - 1; i++)
        node->key[i] = node->key[i + 1];

    node->n--;

    if ((*root)->leaf && (*root)->n == 0) {
        free(*root);
        *root = createNode(1);
    }
}

void deleteTree(BPlusNode *root) {
    if (root == NULL)
        return;

    if (!root->leaf) {
        for (int i = 0; i <= root->n; i++)
            deleteTree(root->child[i]);
    }

    free(root);
}

void display(BPlusNode *root) {
    if (root == NULL)
        return;

    while (!root->leaf)
        root = root->child[0];

    while (root != NULL) {
        for (int i = 0; i < root->n; i++)
            printf("%d ", root->key[i]);

        root = root->next;
    }
}

int main() {
    BPlusNode *root = createTree();

    insertItem(&root, 10);
    insertItem(&root, 20);
    insertItem(&root, 5);
    insertItem(&root, 6);
    insertItem(&root, 12);
    insertItem(&root, 30);
    insertItem(&root, 7);
    insertItem(&root, 17);

    printf("B+ Tree: ");
    display(root);

    deleteItem(&root, 6);

    printf("\nAfter deletion: ");
    display(root);

    if (searchItem(root, 12) != NULL)
        printf("\n12 found");
    else
        printf("\n12 not found");

    deleteTree(root);

    return 0;
}