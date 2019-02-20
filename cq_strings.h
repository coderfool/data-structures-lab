#define MAX 100

typedef struct {
	char **items;
	int front;
	int rear;
} CircularQueue;


int isFull(CircularQueue *cq) {
	return (cq->rear + 1) % MAX == cq->front; 
} 

int isEmpty(CircularQueue *cq) {
	return cq->rear == -1;
}

void insertcq(CircularQueue *cq, char *string) {
	if (isFull(cq)) {
		printf("Queue full!\n");
		return;
	}
	if (cq->front == -1) {
		cq->front = 0;
		cq->rear = 0;
	}
	else {
		cq->rear = (cq->rear + 1) % MAX;
	}
	cq->items[cq->rear] = string;
}

void deletecq(CircularQueue *cq) {
	if (isEmpty(cq)) {
		printf("Queue empty!\n");
		return;
	}
	char *temp = cq->items[cq->front];
	free(temp);
	if (cq->front == cq->rear) {
		cq->front = -1;
		cq->rear = -1;
	}
	else {
		cq->front++;
	}
}

void displaycq(CircularQueue *cq) {
	if (isEmpty(cq)) {
		printf("Queue empty!\n");
		return;
	}
	if (cq->front <= cq->rear) {
		int qPointer = cq->front;
		while (qPointer <= cq->rear) {
			printf("%s ", cq->items[qPointer]);
			qPointer++;
		}
	}
	else {
		int qPointer = cq->front;
		while(qPointer < MAX) {
			printf("%s ", cq->items[qPointer]);
			qPointer++;
		}
		qPointer = 0;
		while (qPointer <= cq->rear) {
			printf("%s ", cq->items[qPointer]);
			qPointer++;
		}
	}
	printf("\n");
}