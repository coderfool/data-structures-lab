#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct NODE * nodePointer;

typedef struct NODE {
    int data;
    nodePointer next;
} Node;

nodePointer newNode(int data) {
    nodePointer node = (nodePointer) malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void insert(nodePointer head, int data) {
    nodePointer node = newNode(data);
    if (head->next == NULL) {
        head->next = node;
        return;
    }
    node->next = head->next;
    head->next = node;
}

void display(nodePointer head) {
    if (head->next == NULL) {
        printf("List empty!\n");
        return;
    }
    nodePointer temp = head->next;
    while(temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

nodePointer merge(nodePointer A, nodePointer B) {
    nodePointer head = newNode(INT_MIN);
    nodePointer a = A->next;
    nodePointer b = B->next;
    nodePointer c = head;
    while (a != NULL && b != NULL) {
        if (a->data < b->data) {
            c->next = newNode(a->data);
            a = a->next; 
            c = c->next;
        }
        else {
            c->next = newNode(b->data);
            b = b->next;
            c = c->next;
        }
    }
    
    while (a != NULL) {
        c->next = newNode(a->data);
        a = a->next;
        c = c->next;
    }
    while (b != NULL) {
        c->next = newNode(b->data);
        b = b->next;
        c = c->next;
    }
    return head; 
}

int main() {
    nodePointer A = newNode(INT_MIN);
    nodePointer B = newNode(INT_MIN);
    insert(A, 5);
    insert(A, 3);
    insert(A, 1);
    insert(B, 4);
    insert(B, 2);
    nodePointer C = merge(A, B);
    display(C);
    return 0;
}
