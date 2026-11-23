#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

int height(Node *root) {
    if (root == NULL)
        return 0;
    return root->height;
}

int max(int a, int b) {
    return a > b ? a : b;
}

Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *createTree() {
    return NULL;
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

int getBalance(Node *root) {
    if (root == NULL)
        return 0;
    return height(root->left) - height(root->right);
}

Node *insertItem(Node *root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insertItem(root->left, data);
    else if (data > root->data)
        root->right = insertItem(root->right, data);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && data < root->left->data)
        return rightRotate(root);

    if (balance < -1 && data > root->right->data)
        return leftRotate(root);

    if (balance > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node *minValueNode(Node *root) {
    Node *current = root;

    while (current->left != NULL)
        current = current->left;

    return current;
}

Node *deleteItem(Node *root, int data) {
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteItem(root->left, data);
    else if (data > root->data)
        root->right = deleteItem(root->right, data);
    else {
        if (root->left == NULL || root->right == NULL) {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                free(root);
                return NULL;
            }

            *root = *temp;
            free(temp);
        } else {
            Node *temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteItem(root->right, temp->data);
        }
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node *searchItem(Node *root, int data) {
    if (root == NULL || root->data == data)
        return root;

    if (data < root->data)
        return searchItem(root->left, data);

    return searchItem(root->right, data);
}

void deleteTree(Node *root) {
    if (root == NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    Node *root = createTree();

    root = insertItem(root, 30);
    root = insertItem(root, 20);
    root = insertItem(root, 40);
    root = insertItem(root, 10);
    root = insertItem(root, 25);
    root = insertItem(root, 35);
    root = insertItem(root, 50);

    printf("AVL Tree: ");
    inorder(root);

    root = deleteItem(root, 20);

    printf("\nAfter deletion: ");
    inorder(root);

    if (searchItem(root, 35) != NULL)
        printf("\n35 found");
    else
        printf("\n35 not found");

    deleteTree(root);

    return 0;
}