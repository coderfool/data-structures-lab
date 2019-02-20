#define MAX 100

typedef struct {
	int items[MAX];
	int front;
	int rear;
} Queue;


int isFull(Queue *cq) {
	return cq->rear == MAX - 1; 
} 

int isEmpty(Queue *cq) {
	return cq->rear == -1;
}

void insertq(Queue *cq, int data) {
	if (isFull(cq)) {
		printf("Queue full!\n");
		return;
	}
	if (cq->front == -1) {
		cq->front = 0;
	}
	cq->rear = cq->rear + 1;
	cq->items[cq->rear] = data;
}

int deleteq(Queue *cq) {
	if (isEmpty(cq)) {
		printf("Queue empty!\n");
		return -99999;
	}
	int deleted = cq->items[cq->front];
	if (cq->front == cq->rear) {
		cq->front = -1;
		cq->rear = -1;
	}
	else {
		cq->front = cq->front + 1;
	}
	return deleted;
}

void displayq(Queue *cq) {
	if (isEmpty(cq)) {
		printf("Queue empty!\n");
	}
	int qPointer = cq->front;
	while (qPointer <= cq->rear) {
		printf("%d ", cq->items[qPointer]);
		qPointer++;
	}
	printf("\n");
}