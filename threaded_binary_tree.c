#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int data;
    int hd;
    struct Node *left;
    struct Node *right;
    int isThreaded;
} *nodePointer;

nodePointer newNode(int data) {
    nodePointer node = malloc(sizeof(struct Node));
    node->data = data;
    node->hd = 0;
    node->isThreaded = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int insert(nodePointer *root, int data, char direction[]) {
    if (*root == NULL && direction[0] == '\0') {
        *root = newNode(data);
        return 0;
    }
    int i = 0;
    nodePointer curr = *root;
    nodePointer prev = NULL;
    while (curr != NULL && direction[i] != '\0') {
        prev = curr;
        if (direction[i] == 'l') curr = curr->left;
        else curr = curr->right;
        i++;
    }
    if (curr == NULL && direction[i] == '\0') {
        if (direction[i - 1] == 'l') prev->left = newNode(data);
        else prev->right = newNode(data);
        return 0;
    }
    return -1;
}

void print(nodePointer root) {
    if (root != NULL) {
        printf("%d ", root->data);
        print(root->left);
        print(root->right);
    }
}

void findHorizontalRange(nodePointer root, int hd, int *min, int *max) {
    if (!root) return;

    if (hd < *min) *min = hd;
    if (hd > *max) *max = hd;

    findHorizontalRange(root->left, hd - 1, min, max);
    findHorizontalRange(root->right, hd + 1, min, max);
}

void printTopView(nodePointer root, int line, int hd) {
    if (!root) return;

    if (line == hd) {
        printf("%d ", root->data);
        return;
    }

    printTopView(root->left, line, hd - 1);
    printTopView(root->right, line, hd + 1);
}

void topView(nodePointer root) {
    int min = INT_MAX;
    int max = 0;
    findHorizontalRange(root, 0, &min, &max);
    for (int i = min; i <= max; i++) {
        printTopView(root, i, 0);
    }
    printf("\n");
}

void topView2(nodePointer root) {
    if (!root) return;
    nodePointer queue[100];
    int front = 0;
    int rear = 0;
    int visited[100];
    for (int i = 0; i < 100; i++)
        visited[i] = INT_MIN;
    int dist;
    queue[rear] = root;
    while (front <= rear) {
        root = queue[front++];
        dist = root->hd;
        if (visited[dist + 50] == INT_MIN) {
            visited[dist + 50] = root->data;
        }

        if (root->left) {
            queue[++rear] = root->left;
            root->left->hd = dist - 1;
        }

        if (root->right) {
            queue[++rear] = root->right;
            root->right->hd = dist + 1;
        }
    }
    for (int i = 0; i < 100; i++) {
        if (visited[i] == INT_MIN) continue;
        printf("%d ", visited[i]);
    }
    printf("\n");
}

void populateQueue(nodePointer root, nodePointer q[], int *front, int *rear) {
    if (root) {
        populateQueue(root->left, q, front, rear);
        q[++(*rear)] = root;
        if (*rear == 0) *front = 0;
        populateQueue(root->right, q, front, rear);
    }
}

void createThreadedUtil(nodePointer root, nodePointer q[], int *front, int *rear) {
    if (root) {
        if (root->left)
            createThreadedUtil(root->left, q, front, rear);
        (*front)++;
        if (root->right)
            createThreadedUtil(root->right, q, front, rear);
        else {
            root->right = q[*front];
            root->isThreaded = 1;
        }
    }
}

void createThreaded(nodePointer root) {
    nodePointer q[100];
    int front = -1;
    int rear = -1;
    populateQueue(root, q, &front, &rear);
    int f = front;
    createThreadedUtil(root, q, &front, &rear);
}

nodePointer leftMost(nodePointer root) {
    if (!root) return NULL;

    while (root->left) root = root->left;
    return root;
}

void inorder(nodePointer root) {
    if (!root) return;

    nodePointer curr = leftMost(root);
    while (curr) {
        printf("%d ", curr->data);
        if (curr->isThreaded)
            curr = curr->right;
        else
            curr = leftMost(curr->right);
    }
    printf("\n");
}

int main() {
    nodePointer root = NULL;
    printf("How many nodes will you enter? >> ");
    int n;
    scanf("%d", &n);
    char direction[100];
    printf("Enter root node >> ");
    int val;
    scanf("%d", &val);
    insert(&root, val, "");
    printf("Enter other nodes:\n");
    for (int i = 1; i < n; i++) {
        printf("Enter node value >> ");
        scanf("%d", &val);
        printf("Enter direction of insertion (l/r) >> ");
        getchar();
        scanf("%s", direction);
        if (insert(&root, val, direction) == -1) {
            printf("Insertion failed! Please enter valid direction.\n");
            i--;
        }
    }
    createThreaded(root);
    inorder(root);
    return 0;
}