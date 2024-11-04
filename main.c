#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUMBER_OF_THREADS 3

void *sort_function(void *params);   
void *merge_function(void *params);          

int *list, *result, SIZE;

typedef struct {
    int start;
    int end;
} ThreadData;

void quick_sort(int arr[], int first, int last);
int partition(int arr[], int first, int last);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <list of integers>\n", argv[0]);
        return -1;
    }

    SIZE = argc - 1;
    list = malloc(SIZE * sizeof(int));
    result = malloc(SIZE * sizeof(int));
    
    for (int i = 0; i < SIZE; i++) {
        list[i] = atoi(argv[i + 1]);
    }

    ThreadData data1, data2;
    data1.start = 0;
    data1.end = (SIZE / 2) - 1; //first half
    data2.start = SIZE / 2;
    data2.end = SIZE - 1; //second half

    pthread_t thread[NUMBER_OF_THREADS];

    printf("Unsorted array: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    pthread_create(&thread[0], NULL, sort_function, (void *)&data1);
    pthread_create(&thread[1], NULL, sort_function, (void *)&data2);
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    printf("Sorted sublist 1: ");
    for (int i = data1.start; i <= data1.end; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    printf("Sorted sublist 2: ");
    for (int i = data2.start; i <= data2.end; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    // merging thread
    pthread_create(&thread[2], NULL, merge_function, NULL);
    pthread_join(thread[2], NULL);

    printf("Merged sorted array: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(list);
    free(result);
    return 0;
}

// implementing Quick Sort
void *sort_function(void *params) {
    ThreadData *data = (ThreadData *) params;
    int start = data->start;
    int end = data->end;

    quick_sort(list, start, end);

    pthread_exit(0);
}

void quick_sort(int arr[], int first, int last) {
    if (first < last) {
        int split = partition(arr, first, last);

        quick_sort(arr, first, split - 1);
        quick_sort(arr, split + 1, last);
    }
}

int partition(int arr[], int first, int last) {
    int pivot = arr[first];
    int ptr_left = first + 1;
    int ptr_right = last;

    bool done = false;
    while (!done) {
        while (ptr_left <= ptr_right && arr[ptr_left] <= pivot) {
                ptr_left++;
        }

        while (arr[ptr_right] >= pivot && ptr_right >= ptr_left) {
                ptr_right--;
        }

        if (ptr_right < ptr_left) {
            done = 1;
        } else {
            int temp = arr[ptr_left];
            arr[ptr_left] = arr[ptr_right];
            arr[ptr_right] = temp;
        }
    }

    int temp = arr[first];
    arr[first] = arr[ptr_right];
    arr[ptr_right] = temp;

    return ptr_right;
}

void *merge_function(void *params) {
    int i = 0, j = SIZE / 2, k = 0;

    for (k = 0; k < SIZE; k++) {
        if (i < SIZE / 2 && (j >= SIZE || list[i] < list[j])) {
            result[k] = list[i++];
        } else {
            result[k] = list[j++];
        }
    }

    pthread_exit(0);
}
