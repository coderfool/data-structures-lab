#include <stdio.h>
#include <stdlib.h>

typedef struct NODE * nodePointer;

typedef struct NODE {
    char data;
    nodePointer left;
    nodePointer right;
} Node;

typedef struct {
    nodePointer items[100];
    int front;
    int rear;
} Queue;

void enqueue(Queue *q, nodePointer node) {
    if (q->rear == -1) {
        q->front = 0;
        q->rear = 0;
        q->items[q->rear] = node;
        return;
    }
    q->items[++(q->rear)] = node;
}

nodePointer dequeue(Queue *q) {
    if (q->front != -1) {
        return q->items[(q->front)++];
    }
}

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

nodePointer delete(nodePointer root, int key) {
    nodePointer curr = root;
    nodePointer parent = NULL;
    while (curr != NULL && curr->data != key) {
        parent = curr;
        if (key < curr->data) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    if (curr == NULL) {
        return root;
    }

    if (curr->left == NULL && curr->right == NULL) {
        if (curr == root) {
            root = NULL;
            free(curr);
            return root;
        }
        (parent->left == curr) ? (parent->left = NULL) : (parent->right = NULL);
    }

    else if (curr->left == NULL || curr->right == NULL) {
        if (curr == root) {
            root = NULL;
            free(curr);
            return root;
        }
        nodePointer child = curr->left ? curr->left : curr->right;
        (parent->left == curr) ? (parent->left = child) : (parent->right = child);
    }

    else {
        nodePointer inorderSuccessor = curr->right;
        nodePointer successorParent = curr;
        while (inorderSuccessor->left != NULL) {
            successorParent = inorderSuccessor;
            inorderSuccessor = inorderSuccessor->left;
        }
        curr->data = inorderSuccessor->data;
        if (successorParent == curr) {
            curr->right = inorderSuccessor->right;
        }
        else {
            (successorParent->left == inorderSuccessor) ? (successorParent->left = NULL) : (successorParent->right = NULL); 
        }
        curr = inorderSuccessor;
    }
    free(curr);
    return root; 
}

void displayLevelOrder(nodePointer root) {
    if (root == NULL) {
        return;
    }
    Queue q;
    q.front = -1;
    q.rear = -1;
    nodePointer curr = NULL;
    enqueue(&q, root);
    while (q.front <= q.rear) {
        curr = dequeue(&q);
        printf("%d ", curr->data);
        if (curr->left) {
            enqueue(&q, curr->left);
        }
        if (curr->right) {
            enqueue(&q, curr->right);
        }
    }
    printf("\n");
}

int main() {
    nodePointer root = NULL;
    int choice = 0;
    int key;
    printf("Binary Search Tree \n1. Insert \n2. Delete \n3. Display \n4. Exit\n");
    while (choice != 4) {
        printf("Enter choice >> ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter key to be inserted >> ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Enter key to be deleted >> ");
                scanf("%d", &key);
                root = delete(root, key);
                break;
            case 3:
                displayLevelOrder(root);
                break;
            case 4: break;
            default: printf("Invalid input!\n");
        }
    }
    return 0;
}