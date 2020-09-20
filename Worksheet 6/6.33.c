#include <stdio.h>

void SortArray(int list[], int n);
void swap(int * i, int * y);

int main(void) {
    int arr[20];

    // scan input
    int len;
    scanf("%d", &len);
    for (int i = 0; i < len; i++){
        scanf("%d", &arr[i]);
    }

    SortArray(arr, len);

    // print output
    for(int i = 0; i < len; i++){
        printf("%d ", arr[i]);
    }
}

// Selection Sort
void SortArray(int list[], int n) {
    for (int i = 0; i < n; i++){
        int min = i;
        // scan for smallest element at index i
        for (int j = i + 1; j < n; j++){
            if (list[j] < list[min]){
                min = j;
            }
        }
        swap(&list[min], &list[i]);
    }
}

// Swap items in array
void swap(int * x, int * y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}