#include <stdio.h>
#include "stack.h"

int main() {
	Stack s1, s2;
	s1.top = -1;
	s2.top = -1;
	int i = 0;
	for (i = 0; i < MAX; i++) {
		s1.items[i] = 0;
		s2.items[i] = 0;
	}
	int choice;
	int data;
	int stackPointer;
	printf("Queue using two stacks\n");
	printf("1. Insert\n2. Delete\n3. Display\n4. Exit\n");
	while (choice != 4) {
		printf("Enter choice >> ");
		scanf("%d", &choice);
		switch(choice) {
			case 1: 
				printf("Enter integer >> ");
				scanf("%d", &data);
				push(&s1, data);
				break;
			case 2:
				if (isEmpty(&s2)) {
					while (!isEmpty(&s1)) {
						int popped = pop(&s1);
						push(&s2, popped);
					}
				}
				printf("Deleted element = %d \n", pop(&s2));
				break;
			case 3:
				stackPointer = s2.top;
				while (stackPointer > -1) {
					printf("%d ", s2.items[stackPointer]);
					stackPointer--;
				}
				stackPointer = 0;
				while (stackPointer <= s1.top) {
					printf("%d ", s1.items[stackPointer]);
					stackPointer++;
				}
				printf("\n");
				break; 
			case 4:
				break;
			default:
				printf("Invalid input!\n");
		}
	}
	return 0;
}