#include <stdio.h>
#include "double_queue.h"

int main() {
    DoubleQueue q;
    q.front[0] = -1;
    q.rear[0] = -1;
    q.front[1] = MAX;
    q.rear[1] = MAX;
    int i;
    for (i = 0; i < MAX; i++) {
        q.items[i] = 0;
    }
    int choice = 0;
    int data;
    printf("Two circular queues in an array\n1. Insert to queue 1\n2. Insert to queue 2\n3. Delete from queue 1\n\
4. Delete from queue 2\n5. Display queue 1\n6. Display queue 2\n7. Exit\n");
    while (choice != 7) {
        printf("Enter choice >> ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter integer >> ");
                scanf("%d", &data);
                insert1(&q, data);
                break;
            case 2:
                printf("Enter integer >> ");
                scanf("%d", &data);
                insert2(&q, data);
                break;
            case 3:
                delete1(&q);
                break;
            case 4:
                delete2(&q);
                break;
            case 5:
                display1(&q);
                break;
            case 6:
                display2(&q);
                break;
            case 7:
                break;
            default:
                printf("Invalid input!\n");
        }
    }
    return 0;
}