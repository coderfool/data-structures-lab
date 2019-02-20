#include <stdio.h>
#include "queue.h"

int search(Queue *q, int key) {
	Queue temp;
	temp.front = -1;
	temp.rear = -1;
	int i;
	for (i = 0; i < MAX; i++) {
		temp.items[i] = 0;
	}
	int found = 0;
	int qPointer = q->front;
	while (qPointer <= q->rear) {
		int deleted = deleteq(q);
		insertq(&temp, deleted);
		if (deleted == key) {
			found = 1;
		}
	}
	qPointer = temp.front;
	while (qPointer <= temp.rear) {
		int deleted = deleteq(&temp);
		insertq(q, deleted);
	}
	return found;
}

int main() {
	Queue q;
	q.front = -1;
	q.rear = -1;
	int i;
	for (i = 0; i < MAX; i++) {
		q.items[i] = 0;
	}
	int choice;
	int data;
	printf("Queue Search\n");
	printf("1. Insert\n2. Delete\n3. Display\n4. Search\n5. Exit\n");
	while (choice != 5) {
		printf("Enter choice >> ");
		scanf("%d", &choice);
		switch(choice) {
			case 1: 
				printf("Enter integer >> ");
				scanf("%d", &data);
				insertq(&q, data);
				break;
			case 2:
				deleteq(&q);
				break;
			case 3:
				displayq(&q);
				break;
			case 4:
				printf("Enter element to search >> ");
				scanf("%d", &data);
				if (search(&q, data)) {
					printf("Element found!\n");
				}
				else {
					printf("Not found!\n");
				}
			case 5:
				break;
			default:
				printf("Invalid input!\n");
		}
	}
	return 0;
}