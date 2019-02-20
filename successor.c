#include <stdio.h>
#include <stdlib.h>

typedef struct NODE * nodePointer;

typedef struct NODE {
    char data;
    nodePointer left;
    nodePointer right;
} Node;

nodePointer newNode(char data) {
    nodePointer node = malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

nodePointer insert(nodePointer root, int key) {
    if (root == NULL) {
        root = newNode(key);
        return root;
    }
    nodePointer parent = NULL;
    nodePointer curr = root;
    while (curr != NULL) {
        parent = curr;
        if (key < curr->data) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    if (key < parent->data) {
        parent->left = newNode(key);
    }
    else {
        parent->right = newNode(key);
    }
    return root;
}

int main() {
    nodePointer root = NULL;
    int n, key;
    printf("Enter number of nodes >> ");
    scanf("%d", &n);
    int i;
    printf("Enter node values >> ");
    for (i = 0; i < n; i++) {
        scanf("%d", &key);
        root = insert(root, key);
    }
    printf("Enter query node >> ");
    scanf("%d", &key);
    nodePointer curr = root;
    while (curr != NULL && curr->data != key) {
        if (key < curr->data) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    if (curr == NULL) {
        printf("Not found! \n");
        return 0;
    }
    nodePointer inorderSuccessor = curr->right;
    while (inorderSuccessor->left != NULL) {
        inorderSuccessor = inorderSuccessor->left;
    }
    if (inorderSuccessor == NULL) {
        printf("Doesn't exist! \n");
    }
    else {
        printf("Inorder successor: %d \n", inorderSuccessor->data);
    }
    return 0;
}