#define MAX 100

typedef struct {
	int items[MAX];
	int front[2];
	int rear[2];
} DoubleQueue;

int isFull1(DoubleQueue *q) {
	return ((q->rear[0] + 1) % MAX == q->front[0]) && ((q->rear[0] + 1 == q->rear[1])); 
}

int isFull2(DoubleQueue *q) {
	return (q->rear[0] + 1 == q->rear[1]) && q->front[1] == MAX - 1; 
}

int isEmpty1(DoubleQueue *q) {
	return q->rear[0] == -1;
}

int isEmpty2(DoubleQueue *q) {
	return q->front[1] == MAX;
}

void insert1(DoubleQueue *q, int data) {
	if (isFull1(q)) {
		printf("Queue full!\n");
		return;
	}
	if (isEmpty1(q)) {
		q->rear[0] = 0;
		q->front[0] = 0;
	}
	else if (q->rear[0] + 1 == q->rear[1]) {
		q->rear[0] = 0;
	}
	else {
		q->rear[0]++;
	}
	q->items[q->rear[0]] = data;
}

void insert2(DoubleQueue *q, int data) {
	if (isFull2(q)) {
		printf("Queue full!\n");
		return;
	}
	if (isEmpty2(q)) {
		q->rear[1] = MAX - 1;
		q->front[1] = MAX - 1;
	}
	else if (q->rear[0] + 1 == q->rear[1]) {
		q->rear[1] = MAX - 1;
	}
	else {
		q->rear[1]--;
	}
	q->items[q->rear[1]] = data;
}

int delete1(DoubleQueue *q) {
	if (isEmpty1(q)) {
		printf("Queue empty!\n");
		return -99999;
	}
	int deleted = q->items[q->front[0]];
	if (q->front[0] == q->rear[0]) {
		q->front[0] = -1;
		q->rear[0] = -1;
	}
	else {
		q->front[0]++;
	}
}

int delete2(DoubleQueue *q) {
	if (isEmpty2(q)) {
		printf("Queue empty!\n");
		return -99999;
	}
	int deleted = q->items[q->front[1]];
	if (q->front[1] == q->rear[1]) {
		q->front[1] = MAX - 1;
		q->rear[1] = MAX - 1;
	}
	else {
		q->front[1]--;
	}
}

void display1(DoubleQueue *q) {
	if (isEmpty1(q)) {
		printf("Queue empty!\n");
	}
	if (q->front[0] <= q->rear[0]) {
		int qPointer = q->front[0];
		while (qPointer <= q->rear[0]) {
			printf("%d ", q->items[qPointer]);
			qPointer++;
		}
	}
	else {
		int qPointer = q->front[0];
		while(qPointer < MAX) {
			printf("%s ", q->items[qPointer]);
		}
		qPointer = 0;
		while (qPointer <= q->rear[0]) {
			printf("%s ", q->items[qPointer]);
			qPointer++;
		}
	}
	printf("\n");
}

void display2(DoubleQueue *q) {
	if (isEmpty2(q)) {
		printf("Queue empty!\n");
	}
	if (q->front[1] >= q->rear[1]) {
		int qPointer = q->front[1];
		while (qPointer >= q->rear[1]) {
			printf("%d ", q->items[qPointer]);
			qPointer--;
		}
	}
	else {
		int qPointer = q->front[1];
		while(qPointer > q->rear[0]) {
			printf("%s ", q->items[qPointer]);
			qPointer--;
		}
		qPointer = MAX - 1;
		while (qPointer >= q->rear[1]) {
			printf("%s ", q->items[qPointer]);
			qPointer--;
		}
	}
	printf("\n");
}