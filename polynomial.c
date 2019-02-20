#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct NODE * nodePointer;

typedef struct NODE {
    int coeff;
    int power;
    nodePointer next;
} Node;

nodePointer newNode(int c, int p) {
    nodePointer node = (nodePointer) malloc(sizeof(Node));
    node->coeff = c;
    node->power = p;
    node->next = NULL;
    return node;
}

void insert(nodePointer head, int c, int p) {
    nodePointer node = newNode(c, p);
    if (head->next == NULL) {
        head->next = node;
        return;
    }
    node->next = head->next;
    head->next = node;
}

void attach(nodePointer head, int c, int p) {
    nodePointer node = newNode(c, p);
    nodePointer tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = node;
}

void display(nodePointer head) {
    if (head->next == NULL) {
        printf("List empty!\n");
        return;
    }
    nodePointer temp = head->next;
    while(temp) {
        printf("%dx^%d ", temp->coeff, temp->power);
        temp = temp->next;
    }
    printf("\n");
}

void insertInPlace(nodePointer head, nodePointer node) {
    if (head->next == NULL) {
        head->next = node;
        return;
    }
    nodePointer temp = head->next;
    nodePointer prev = head;
    while (temp != NULL && temp->power > node->power) {
        prev = temp;
        temp = temp->next;
    }
    if (temp != NULL && temp->power == node->power) {
        temp->coeff += node->coeff;
    }
    else {
        node->next = prev->next;
        prev->next = node;
    }
}

nodePointer add(nodePointer a, nodePointer b) {
    nodePointer res = newNode(INT_MIN, INT_MIN);
    a = a->next;
    b = b->next;
    while (a != NULL && b != NULL) {
        if (a->power > b->power) {
            attach(res, a->coeff, a->power);
            a = a->next;
        }
        else if (a->power < b->power) {
            attach(res, b->coeff, b->power);
            b = b->next;
        }
        else {
            attach(res, a->coeff + b->coeff, a->power);
            a = a->next;
            b = b->next;
        }
    }

    while (a != NULL) {
        attach(res, a->coeff, a->power);
        a = a->next;
    }

    while (b != NULL) {
        attach(res, b->coeff, b->power);
        b = b->next;
    }

    return res;
}

nodePointer multiply(nodePointer a, nodePointer b) {
    nodePointer res = newNode(INT_MIN, INT_MIN);
    nodePointer tempA = a->next;
    while (tempA != NULL) {
        nodePointer tempB = b->next;
        while (tempB != NULL) {
            nodePointer node = newNode(tempA->coeff * tempB->coeff, tempA->power + tempB->power);
            insertInPlace(res, node);
            tempB = tempB->next;
        }
        tempA = tempA->next;
    }
    return res;
}

int main() {
    nodePointer a = newNode(INT_MIN, INT_MIN);
    nodePointer b = newNode(INT_MIN, INT_MIN);
    int n;
    printf("Enter number of terms in first polynomial >> ");
    scanf("%d", &n);
    printf("Enter terms of first polynomial >> ");
    int coeff, power;
    int i = 0;
    while (i < n) {
        scanf("%d %d", &coeff, &power);
        attach(a, coeff, power);
        i++;
    }
    printf("Enter number of terms in second polynomial >> ");
    scanf("%d", &n);
    printf("Enter terms of second polynomial >> ");
    i = 0;
    while (i < n) {
        scanf("%d %d", &coeff, &power);
        attach(b, coeff, power);
        i++;
    }
    nodePointer sum = add(a, b);
    nodePointer prod = multiply(a, b);
    printf("Sum: ");
    display(sum);
    printf("Product: ");
    display(prod);
    return 0;
}
