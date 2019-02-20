#include <stdio.h>
#include <stdlib.h> 
#include "cq_strings.h"

int main() {
	CircularQueue cq;
	cq.front = -1;
	cq.rear = -1;
	cq.items = (char **)malloc(MAX * sizeof(char *));
	int i;
	int choice = 0;
	char newline;
	printf("Circular Queue of Strings\n");
	printf("1. Insert\n2. Delete\n3. Display\n4. Exit\n");
	while (choice != 4) {
		printf("Enter choice >> ");
		scanf("%d", &choice);
		scanf("%c", &newline);
		switch(choice) {
			case 1:
				printf("Enter string >> ");
				char *string = malloc(MAX * sizeof(char));
				gets(string);
				insertcq(&cq, string);
				break;
			case 2:
				deletecq(&cq);
				break;
			case 3:
				displaycq(&cq);
				break;
			case 4:
				break;
			default: 
				printf("Invalid input!\n");
		}
	}
	return 0;
}