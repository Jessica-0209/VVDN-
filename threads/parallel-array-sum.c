#include <stdio.h>
#include <pthread.h>

#define SIZE 1000
#define THREAD_COUNT 2

int array[SIZE];
int sum[THREAD_COUNT];

void* partial_sum(void* arg) {
    int id = *(int*)arg;
    int start = id * (SIZE / THREAD_COUNT);
    int end = start + (SIZE / THREAD_COUNT);

    sum[id] = 0;
    for (int i = start; i < end; i++) {
        sum[id] += array[i];
    }

    return NULL;
}

int main() {
    pthread_t threads[THREAD_COUNT];
    int ids[THREAD_COUNT];

    // Fill array
    for (int i = 0; i < SIZE; i++) array[i] = 1;

    // Create threads
    for (int i = 0; i < THREAD_COUNT; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, partial_sum, &ids[i]);
    }

    // Wait for threads
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    	// Combine results
    	int total = 0;
    	for (int i = 0; i < THREAD_COUNT; i++) 
    	{
        	total += sum[i];
    	}

    	printf("Total sum = %d\n", total);
    	return 0;
}

