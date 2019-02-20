#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void quicksort(int arr[], int left, int right) {
    if (left >= right) return;

    int leftPointer = left - 1;
    int rightPointer = right + 1;
    int pivot = arr[left];
    while (leftPointer < rightPointer) {
        while (leftPointer < right && arr[++leftPointer] <= pivot);
        while (rightPointer > 0 && arr[--rightPointer] > pivot);
        if (leftPointer < rightPointer) {
            swap(&arr[leftPointer], &arr[rightPointer]);
        }
    }
    swap(&arr[left], &arr[rightPointer]);
    quicksort(arr, left, rightPointer - 1);
    quicksort(arr, rightPointer + 1, right);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int *arr = calloc(n, sizeof(int));
        for (int i = 0; i < n; i++)
            scanf("%d", &arr[i]);
        quicksort(arr, 0, n - 1);
        for (int i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }
    return 0;
}