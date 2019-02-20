#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 100

int compute(char *operator, int a, int b) {
    char op = operator[0];
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
    }
}

int main() {
    char str[MAX];
    fgets(str, MAX, stdin);
    char *token = str;
    char *arr[MAX];
    int i = 0;
    for (i = 0; i < MAX; i++) {
        arr[i] = malloc(20 * sizeof(char));
    }
    i = 0;
    while (token = strtok(token, " ")) {
        arr[i++] = token;
        token = NULL;
    }
    int len = i;
    int ok = 1;
    char *queue[MAX];
    for (i = 0; i < MAX; i++) {
        queue[i] = malloc(20 * sizeof(char));
    }
    while (len > 1) {
        int front = -1;
        int rear = -1;
        for (i = 0; i < len; i++) {
            if (!strtol(arr[i], NULL, 10)) {
                if (i > len - 3) {
                    ok = 0;
                    printf("Invalid input!\n");
                    break;
                }
                if (strtol(arr[i + 1], NULL, 10) && strtol(arr[i + 2], NULL, 10)) {
                    int val = compute(arr[i], strtol(arr[i + 1], NULL, 10), strtol(arr[i + 2], NULL, 10));
                    printf("Computing %s %s %s = %d \n", arr[i + 1], arr[i], arr[i + 2], val);
                    char *buf = malloc(20 * sizeof(char));
                    sprintf(buf, "%d", val);
                    queue[++rear] = buf;
                    i += 2;
                }
                else {
                    queue[++rear] = arr[i];
                }
            }
            else {
                queue[++rear] = arr[i];
            }
            if (rear == 0) front = 0;
        }
        if (!ok) break;
        len = rear - front + 1;
        int j = 0;
        printf("Expression: ");
        while (front <= rear) {
            printf("%s ", queue[front]);
            arr[j++] = queue[front++];
        }
    }
    return 0;
}