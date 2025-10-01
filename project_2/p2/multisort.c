#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10

// Global arrays
int unsorted_array[ARRAY_SIZE] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8}; 
int sorted_array[ARRAY_SIZE];

typedef struct {
    int start_index;
    int end_index;
} parameters;

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void *sorter(void *params) {
    parameters *p = (parameters *)params;
    int start = p->start_index;
    int end = p->end_index;
    int size = end - start + 1;

    qsort(&unsorted_array[start], size, sizeof(int), compare);
    
    pthread_exit(0);
}

void *merger(void *params) {
    int i = 0; 
    int j = ARRAY_SIZE / 2; 
    int k = 0; 

    while (i < ARRAY_SIZE / 2 && j < ARRAY_SIZE) {
        if (unsorted_array[i] < unsorted_array[j]) {
            sorted_array[k++] = unsorted_array[i++];
        } else {
            sorted_array[k++] = unsorted_array[j++];
        }
    }

    while (i < ARRAY_SIZE / 2) {
        sorted_array[k++] = unsorted_array[i++];
    }
    while (j < ARRAY_SIZE) {
        sorted_array[k++] = unsorted_array[j++];
    }
    
    pthread_exit(0);
}

int main() {
    pthread_t tid1, tid2, tid3; 

    printf("Original array: ");
    print_array(unsorted_array, ARRAY_SIZE);

    parameters params1 = {0, (ARRAY_SIZE / 2) - 1};
    parameters params2 = {ARRAY_SIZE / 2, ARRAY_SIZE - 1};

    pthread_create(&tid1, NULL, sorter, &params1);
    pthread_create(&tid2, NULL, sorter, &params2);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_create(&tid3, NULL, merger, NULL);

    pthread_join(tid3, NULL);

    printf("Sorted array:   ");
    print_array(sorted_array, ARRAY_SIZE);

    return 0;
}
