#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

int isOperand(char op) {
    return op >= '0' && op <= '9';
}

nodePointer createPostfixTree(char expr[]) {
    nodePointer stack[100];
    int top = -1;
    int i = 0;
    while (expr[i + 1] != '\0') {
        if (isOperand(expr[i])) {
            stack[++top] = newNode(expr[i]);
        }
        else {
            nodePointer node = newNode(expr[i]);
            node->right = stack[top--];
            node->left = stack[top--];
            stack[++top] = node;
        }
        i++;
    }
    return stack[top];
}

float evaluate(nodePointer root) {
    switch(root->data) {
        case '+' : return evaluate(root->left) + evaluate(root->right);
        case '-' : return evaluate(root->left) - evaluate(root->right);
        case '*' : return evaluate(root->left) * evaluate(root->right);
        case '/' : return evaluate(root->left) / evaluate(root->right);
        case '^' : return pow(evaluate(root->left), evaluate(root->right));
        default: return root->data - '0';
    }
}

int main() {
    char expr[100];
    printf("Enter postfix expression >> ");
    fgets(expr, 100, stdin);
    nodePointer root = createPostfixTree(expr);
    printf("Value: %.2f", evaluate(root));
    printf("\n");
    return 0;
}