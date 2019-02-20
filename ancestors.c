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

nodePointer createLevelOrder() {
    int n;
    printf("Enter number of nodes >> ");
    scanf("%d", &n);
    int *nodes = malloc(sizeof(int) * n);
    int i;
    printf("Enter node values >> ");
    for (i = 0; i < n; i++) {
        scanf("%d", &nodes[i]);
    }
    nodePointer root = newNode(nodes[0]);
    Queue q;
    q.front = -1;
    q.rear = -1;
    enqueue(&q, root);
    i = 0;
    while (i < n) {
        nodePointer curr = dequeue(&q);
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n) {
            curr->left = newNode(nodes[left]);
            enqueue(&q, curr->left);
        }
        if (right < n) {
            curr->right = newNode(nodes[right]);
            enqueue(&q, curr->right);
        }
        i++;
    }
    return root;
}

int printAncestors(nodePointer root, int key) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == key) {
        return 1;
    }
    if (printAncestors(root->left, key) || printAncestors(root->right, key)) {
        printf("%d ", root->data);
        return 1;
    }
    return 0;
}

int main() {
    nodePointer root = createLevelOrder();
    int key;
    printf("Enter key >> ");
    scanf("%d", &key);
    printf("Ancestors: ");
    printAncestors(root, key);
    printf("\n");
    return 0;
}