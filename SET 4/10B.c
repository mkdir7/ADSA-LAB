#include <stdio.h>
#include <stdlib.h>

#define T 3

typedef struct BTreeNode {
    int key[2 * T - 1];
    struct BTreeNode *child[2 * T];
    int n;
    int leaf;
} BTreeNode;

BTreeNode *createNode(int leaf) {
    BTreeNode *node = (BTreeNode *)malloc(sizeof(BTreeNode));

    node->n = 0;
    node->leaf = leaf;

    for (int i = 0; i < 2 * T; i++)
        node->child[i] = NULL;

    return node;
}

BTreeNode *createTree() {
    return createNode(1);
}

BTreeNode *searchItem(BTreeNode *root, int key) {
    if (root == NULL)
        return NULL;

    int i = 0;

    while (i < root->n && key > root->key[i])
        i++;

    if (i < root->n && key == root->key[i])
        return root;

    if (root->leaf)
        return NULL;

    return searchItem(root->child[i], key);
}

void splitChild(BTreeNode *parent, int index) {
    BTreeNode *y = parent->child[index];
    BTreeNode *z = createNode(y->leaf);

    z->n = T - 1;

    for (int j = 0; j < T - 1; j++)
        z->key[j] = y->key[j + T];

    if (!y->leaf) {
        for (int j = 0; j < T; j++)
            z->child[j] = y->child[j + T];
    }

    y->n = T - 1;

    for (int j = parent->n; j >= index + 1; j--)
        parent->child[j + 1] = parent->child[j];

    parent->child[index + 1] = z;

    for (int j = parent->n - 1; j >= index; j--)
        parent->key[j + 1] = parent->key[j];

    parent->key[index] = y->key[T - 1];
    parent->n++;
}

void insertNonFull(BTreeNode *root, int key) {
    int i = root->n - 1;

    if (root->leaf) {
        while (i >= 0 && key < root->key[i]) {
            root->key[i + 1] = root->key[i];
            i--;
        }

        root->key[i + 1] = key;
        root->n++;
    } else {
        while (i >= 0 && key < root->key[i])
            i--;

        i++;

        if (root->child[i]->n == 2 * T - 1) {
            splitChild(root, i);

            if (key > root->key[i])
                i++;
        }

        insertNonFull(root->child[i], key);
    }
}

void insertItem(BTreeNode **root, int key) {
    if (searchItem(*root, key) != NULL)
        return;

    if ((*root)->n == 2 * T - 1) {
        BTreeNode *newRoot = createNode(0);

        newRoot->child[0] = *root;

        splitChild(newRoot, 0);

        *root = newRoot;

        insertNonFull(newRoot, key);
    } else {
        insertNonFull(*root, key);
    }
}

int findKey(BTreeNode *root, int key) {
    int index = 0;

    while (index < root->n && root->key[index] < key)
        index++;

    return index;
}

void removeFromLeaf(BTreeNode *root, int index) {
    for (int i = index + 1; i < root->n; i++)
        root->key[i - 1] = root->key[i];

    root->n--;
}

int getPredecessor(BTreeNode *root) {
    while (!root->leaf)
        root = root->child[root->n];

    return root->key[root->n - 1];
}

int getSuccessor(BTreeNode *root) {
    while (!root->leaf)
        root = root->child[0];

    return root->key[0];
}

void borrowFromPrevious(BTreeNode *root, int index) {
    BTreeNode *child = root->child[index];
    BTreeNode *sibling = root->child[index - 1];

    for (int i = child->n - 1; i >= 0; i--)
        child->key[i + 1] = child->key[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; i--)
            child->child[i + 1] = child->child[i];

        child->child[0] = sibling->child[sibling->n];
    }

    child->key[0] = root->key[index - 1];
    root->key[index - 1] = sibling->key[sibling->n - 1];

    child->n++;
    sibling->n--;
}

void borrowFromNext(BTreeNode *root, int index) {
    BTreeNode *child = root->child[index];
    BTreeNode *sibling = root->child[index + 1];

    child->key[child->n] = root->key[index];

    if (!child->leaf)
        child->child[child->n + 1] = sibling->child[0];

    root->key[index] = sibling->key[0];

    for (int i = 1; i < sibling->n; i++)
        sibling->key[i - 1] = sibling->key[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; i++)
            sibling->child[i - 1] = sibling->child[i];
    }

    child->n++;
    sibling->n--;
}

void merge(BTreeNode *root, int index) {
    BTreeNode *child = root->child[index];
    BTreeNode *sibling = root->child[index + 1];

    child->key[T - 1] = root->key[index];

    for (int i = 0; i < sibling->n; i++)
        child->key[i + T] = sibling->key[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; i++)
            child->child[i + T] = sibling->child[i];
    }

    for (int i = index + 1; i < root->n; i++)
        root->key[i - 1] = root->key[i];

    for (int i = index + 2; i <= root->n; i++)
        root->child[i - 1] = root->child[i];

    child->n += sibling->n + 1;
    root->n--;

    free(sibling);
}

void deleteFromNode(BTreeNode *root, int key) {
    int index = findKey(root, key);

    if (index < root->n && root->key[index] == key) {
        if (root->leaf) {
            removeFromLeaf(root, index);
            return;
        }

        if (root->child[index]->n >= T) {
            int predecessor = getPredecessor(root->child[index]);
            root->key[index] = predecessor;
            deleteFromNode(root->child[index], predecessor);
        } else if (root->child[index + 1]->n >= T) {
            int successor = getSuccessor(root->child[index + 1]);
            root->key[index] = successor;
            deleteFromNode(root->child[index + 1], successor);
        } else {
            merge(root, index);
            deleteFromNode(root->child[index], key);
        }
    } else {
        if (root->leaf)
            return;

        int flag = index == root->n;

        if (root->child[index]->n < T) {
            if (index != 0 && root->child[index - 1]->n >= T)
                borrowFromPrevious(root, index);
            else if (index != root->n && root->child[index + 1]->n >= T)
                borrowFromNext(root, index);
            else {
                if (index != root->n)
                    merge(root, index);
                else
                    merge(root, index - 1);
            }
        }

        if (flag && index > root->n)
            deleteFromNode(root->child[index - 1], key);
        else
            deleteFromNode(root->child[index], key);
    }
}

void deleteItem(BTreeNode **root, int key) {
    if (*root == NULL)
        return;

    if (searchItem(*root, key) == NULL)
        return;

    deleteFromNode(*root, key);

    if ((*root)->n == 0 && !(*root)->leaf) {
        BTreeNode *temp = *root;
        *root = (*root)->child[0];
        free(temp);
    }
}

void deleteTree(BTreeNode *root) {
    if (root == NULL)
        return;

    if (!root->leaf) {
        for (int i = 0; i <= root->n; i++)
            deleteTree(root->child[i]);
    }

    free(root);
}

void traverse(BTreeNode *root) {
    if (root == NULL)
        return;

    int i;

    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            traverse(root->child[i]);

        printf("%d ", root->key[i]);
    }

    if (!root->leaf)
        traverse(root->child[i]);
}

int main() {
    BTreeNode *root = createTree();

    insertItem(&root, 10);
    insertItem(&root, 20);
    insertItem(&root, 5);
    insertItem(&root, 6);
    insertItem(&root, 12);
    insertItem(&root, 30);
    insertItem(&root, 7);
    insertItem(&root, 17);

    printf("B-Tree: ");
    traverse(root);

    deleteItem(&root, 6);

    printf("\nAfter deletion: ");
    traverse(root);

    if (searchItem(root, 12) != NULL)
        printf("\n12 found");
    else
        printf("\n12 not found");

    deleteTree(root);

    return 0;
}