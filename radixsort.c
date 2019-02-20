#include <stdio.h>
#include <limits.h>
#define MAX 100

int getMax(int arr[], int n) {
    int max = arr[0];
    for(int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

void radixSort(int arr[], int n) {
    int max = getMax(arr, n);
    for (int b = 1; max / b > 0; b *= 10) {
        int count[10] = {0};
        for(int i = 0; i < n; i++) {
            count[(arr[i] / b) % 10]++;
        }
        for(int i = 1; i < n; i++) {
            count[i] += count[i - 1];
        }
        int res[MAX];
        for(int i = n - 1; i > -1; i--) {
            res[count[(arr[i] / b) % 10] - 1] = arr[i];
            count[(arr[i] / b) % 10]--;
        }
        for(int i = 0; i < n; i++) {
            arr[i] = res[i];
        }
    }
}

int main(int argc, char const *argv[])
{
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66, 77, 55, 74, 48};
    int n = sizeof(arr) / sizeof(arr[0]);
    radixSort(arr, n);
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    return 0;
}
