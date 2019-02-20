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

nodePointer Union(nodePointer a, nodePointer b) {
    nodePointer res = newNode(INT_MIN);
    nodePointer temp = a->next;
    while (temp != NULL) {
        insert(res, temp->data);
        temp = temp->next;
    }
    nodePointer tempB = b->next;
    while (tempB != NULL) {
        temp = a->next;
        int found = 0;
        while (temp != NULL) {
            if (tempB->data == temp->data) {
                found = 1;
                break;
            }
            temp = temp->next;
        }
        if (!found) {
            insert(res, tempB->data);
        }
        tempB = tempB->next;
    }
    return res;
}

nodePointer intersection(nodePointer a, nodePointer b) {
    nodePointer res = newNode(INT_MIN);
    nodePointer tempA = a->next;
    while (tempA != NULL) {
        nodePointer tempB = b->next;
        int present = 0;
        while (tempB != NULL) {
            if (tempA->data == tempB->data) {
                present = 1;
                break;
            }
            tempB = tempB->next;
        }
        if (present) {
            insert(res, tempA->data);
        }
        tempA = tempA->next;
    }
    return res;
}

int main() {
    nodePointer a = newNode(INT_MIN);
    nodePointer b = newNode(INT_MIN);
    int n;
    printf("Enter number of elements in first set >> ");
    scanf("%d", &n);
    printf("Enter elements in first set >> ");
    int element;
    int i = 0;
    while (i < n) {
        scanf("%d", &element);
        insert(a, element);
        i++;
    }
    printf("Enter number of elements in second set >> ");
    scanf("%d", &n);
    printf("Enter elements in second set >> ");
    i = 0;
    while (i < n) {
        scanf("%d", &element);
        insert(b, element);
        i++;
    }
    nodePointer uni = Union(a, b);
    nodePointer inter = intersection(a, b);
    printf("Union: ");
    display(uni);
    printf("Intersection: ");
    display(inter);
    return 0;
}
