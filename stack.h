#define MAX 100

typedef struct {
	int items[MAX];
	int top;
} Stack;


int isFull(Stack *s) {
	return s->top == MAX - 1;
}

int isEmpty(Stack *s) {
	return s->top == -1;
}

void push(Stack *s, int data) {
	if (isFull(s)) {
		printf("Stack Overflow!\n");
		return;
	}
	s->top++;
	s->items[s->top] = data;
}

int pop(Stack *s) {
	if (isEmpty(s)) {
		printf("Stack Underflow!\n");
		return -99999;
	}
	int popped = s->items[s->top];
	s->top--;
	return popped;
}