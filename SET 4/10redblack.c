#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

typedef struct Node {
    int data;
    int color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

Node *NIL;

Node *createTree() {
    NIL = (Node *)malloc(sizeof(Node));
    NIL->color = BLACK;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
    return NIL;
}

Node *createNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));

    node->data = data;
    node->color = RED;
    node->left = NIL;
    node->right = NIL;
    node->parent = NIL;

    return node;
}

void leftRotate(Node **root, Node *x) {
    Node *y = x->right;

    x->right = y->left;

    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rightRotate(Node **root, Node *y) {
    Node *x = y->left;

    y->left = x->right;

    if (x->right != NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NIL)
        *root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

void insertFix(Node **root, Node *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }

    (*root)->color = BLACK;
}

void insertItem(Node **root, int data) {
    Node *z = createNode(data);
    Node *y = NIL;
    Node *x = *root;

    while (x != NIL) {
        y = x;

        if (data < x->data)
            x = x->left;
        else if (data > x->data)
            x = x->right;
        else {
            free(z);
            return;
        }
    }

    z->parent = y;

    if (y == NIL)
        *root = z;
    else if (data < y->data)
        y->left = z;
    else
        y->right = z;

    insertFix(root, z);
}

Node *searchItem(Node *root, int data) {
    while (root != NIL) {
        if (data == root->data)
            return root;

        if (data < root->data)
            root = root->left;
        else
            root = root->right;
    }

    return NULL;
}

Node *minimum(Node *root) {
    while (root->left != NIL)
        root = root->left;

    return root;
}

void transplant(Node **root, Node *u, Node *v) {
    if (u->parent == NIL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}

void deleteFix(Node **root, Node *x) {
    while (x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            Node *w = x->parent->left;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }

    x->color = BLACK;
}

void deleteItem(Node **root, int data) {
    Node *z = searchItem(*root, data);

    if (z == NULL)
        return;

    Node *y = z;
    Node *x;
    int originalColor = y->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = minimum(z->right);
        originalColor = y->color;
        x = y->right;

        if (y->parent == z)
            x->parent = y;
        else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (originalColor == BLACK)
        deleteFix(root, x);
}

void deleteTree(Node *root) {
    if (root == NIL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

void inorder(Node *root) {
    if (root != NIL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    Node *root = createTree();

    insertItem(&root, 30);
    insertItem(&root, 20);
    insertItem(&root, 40);
    insertItem(&root, 10);
    insertItem(&root, 25);
    insertItem(&root, 35);
    insertItem(&root, 50);

    printf("Red-Black Tree: ");
    inorder(root);

    deleteItem(&root, 20);

    printf("\nAfter deletion: ");
    inorder(root);

    if (searchItem(root, 35) != NULL)
        printf("\n35 found");
    else
        printf("\n35 not found");

    deleteTree(root);
    free(NIL);

    return 0;
}