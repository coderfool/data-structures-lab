#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} *nodePointer;

nodePointer newNode(int data) {
    nodePointer node = malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void print(nodePointer root) {
    if (root != NULL) {
        printf("%d ", root->data);
        print(root->left);
        print(root->right);
    }
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

int height(nodePointer root, nodePointer *commonNode, int *dia, int *leftHeight, int *rightHeight) {
    if (!root) return 0;

    int l = height(root->left, commonNode, dia, leftHeight, rightHeight);
    int r = height(root->right, commonNode, dia, leftHeight, rightHeight);
    if (*dia < 1 + l + r) {
        *dia = 1 + l + r;
        *leftHeight = l;
        *rightHeight = r;
        *commonNode = root;
    }
    return 1 + max(l, r);
}

void printPath(int path[], int n, char flag) {
    if (flag == 'l') {
        for (int i = n - 1; i > -1; i--)
            printf("%d ", path[i]);
    }
    else if (flag == 'r') {
        for (int i = 0; i < n; i++)
            printf("%d ", path[i]);
    }
}

void printHalfPath(nodePointer root, int path[], int pathLen, int maxDepth, char *flag) {
    if (!root) return;

    path[pathLen++] = root->data;
    if (root->left == NULL && root->right == NULL) {
        if (pathLen == maxDepth && (*flag == 'l' || *flag == 'r')) {
            printPath(path, pathLen, *flag);
            *flag = '\0';
        }
    }
    else {
        printHalfPath(root->left, path, pathLen, maxDepth, flag);
        printHalfPath(root->right, path, pathLen, maxDepth, flag);
    }
}

void printLongestDiameter(nodePointer root) {
    int dia = INT_MIN;
    int leftPath[100], rightPath[100];
    int leftHeight = 0, rightHeight = 0;
    nodePointer commonNode = root;
    int h = height(root, &commonNode, &dia, &leftHeight, &rightHeight);
    char flag = 'l';
    printHalfPath(commonNode->left, leftPath, 0, leftHeight, &flag);
    printf("%d \n", commonNode->data);
    flag = 'r';
    printHalfPath(commonNode->right, rightPath, 0, rightHeight, &flag);
}

int hasPath(nodePointer root, int key, int path[], int *pathLen) {
    if (!root) return 0;

    path[(*pathLen)++] = root->data;
    if (root->data == key) return 1;
    if (hasPath(root->left,  key, path, pathLen) || hasPath(root->right, key, path, pathLen)) return 1;
    (*pathLen)--;
    return 0;
}

int LCA(nodePointer root, int x, int y) {
    if (!root) return INT_MIN;

    int pathX[100], pathY[100];
    int xLen = 0, yLen = 0;
    int lca = INT_MIN;
    if (hasPath(root, x, pathX, &xLen) && hasPath(root, y, pathY, &yLen)) {
        int i;
        for (i = 0; i < xLen && i < yLen; i++) {
            if (pathX[i] != pathY[i]) break;
        }
        lca = pathX[i - 1];
    }
    return lca;
}

int distance(nodePointer root, int key) {
    int path[100];
    int pathLen = 0;
    if(hasPath(root, key, path, &pathLen)) return pathLen; 
    return INT_MIN;
}

int dist(nodePointer root, int x, int y) {
    int lca = LCA(root, x, y);
    if (lca == INT_MIN) return lca;
    return distance(root, x) + distance(root, y) - 2 * distance(root, lca);
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
    // int x, y;
    // printf("Enter input nodes >> ");
    // scanf("%d %d", &x, &y);
    // int d = dist(root, x, y);
    // if (d == INT_MIN) printf("Invalid input!\n");
    // else printf("Distance = %d \n", d);
    printLongestDiameter(root);
    return 0;
}