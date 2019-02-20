#include <stdio.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(int heap[], int node, int size) {
    int parent = node;
    while(parent <= size / 2) {
        int left = 2 * parent;
        int right = 2 * parent + 1;
        int min = parent;
        if (left <= size && heap[left] < heap[parent]) {
            min = left;
        }
        if (right <= size && heap[right] < heap[min]) {
            min = right;
        }
        if (min == parent) break;
        swap(&heap[parent], &heap[min]);
        parent = min;
    }
}


void buildHeap(int heap[], int size) {
    for (int i = size / 2; i >= 1; i--) {
        minHeapify(heap, i, size);
    }
}

void heapSort(int arr[], int size) {
    int s = size;
    buildHeap(arr, size);
    while(size > 1) {
        swap(&arr[size], &arr[1]);
        size--; 
        minHeapify(arr, 1, size);
    }
}

int main() {
    int heap[] = {0, 7, 17, 2, 31, 1, 19, 12};
    int n = sizeof(heap) / sizeof(heap[0]);
    heapSort(heap, n);
    for(int i = 1; i < n; i++)
        printf("%d ", heap[i]);
    return 0;
}