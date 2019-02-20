#include <stdio.h>
#include <stdlib.h>

typedef struct NODE * nodePointer;

typedef struct NODE {
    int data;
    nodePointer leftChild;
    nodePointer rightChild;
} Node;

typedef struct {
    nodePointer items[100];
    int front;
    int rear;
} Queue;

nodePointer newNode(int data) {
    nodePointer node = malloc(sizeof(Node));
    node->data = data;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

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
            curr->leftChild = newNode(nodes[left]);
            enqueue(&q, curr->leftChild);
        }
        if (right < n) {
            curr->rightChild = newNode(nodes[right]);
            enqueue(&q, curr->rightChild);
        }
        i++;
    }
    return root;
}

void inorder(nodePointer root) {
    if (root != NULL) {
        inorder(root->leftChild);
        printf("%d ", root->data);
        inorder(root->rightChild);
    }
}

void preorder(nodePointer root) {
    if (!root) {
        return;
    }
    nodePointer stack[100];
    int top = -1;
    stack[++top] = root;
    nodePointer curr = NULL;
    while (top > -1) {
        curr = stack[top--];
        printf("%d ", curr->data);
        if (curr->rightChild) {
            stack[++top] = curr->rightChild;
        }
        if (curr->leftChild) {
            stack[++top] = curr->leftChild;
        }
    }
}

void postorder(nodePointer root) {
    if (!root) {
        return;
    }
    nodePointer stack[100];
    int top = -1;
    stack[++top] = root;
    nodePointer curr = NULL;
    nodePointer prev = NULL;
    while (top > -1) {
        curr = stack[top];
        if (!prev || prev->leftChild == curr || prev->rightChild == curr) {
            if (curr->leftChild) {
                stack[++top] = curr->leftChild;
            }
            else if (curr->rightChild) {
                stack[++top] = curr->rightChild;
            }
        }
        else if (curr->leftChild == prev) {
            if (curr->rightChild) {
                stack[++top] = curr->rightChild;
            }
        }
        else { 
            printf("%d ", curr->data);
            top--;
        }
        prev = curr;
    }   
}

int main() {
    nodePointer root = createLevelOrder();
    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");
    printf("Postorder traversal: ");
    postorder(root);
    printf("\n");
    return 0;
}