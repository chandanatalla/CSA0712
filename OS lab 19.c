
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>

pthread_mutex_t lock;
int counter = 0;

void* process(void* arg) {
    pthread_mutex_lock(&lock);

    // Critical Section
    counter++;
    printf("Thread %d entered critical section. Counter = %d\n", *((int*)arg), counter);
    Sleep(1000); // Simulate processing delay

    printf("Thread %d leaving critical section.\n", *((int*)arg));
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t threads[5];
    int thread_ids[5];

    // Initialize mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed.\n");
        return 1;
    }

    // Create threads
    for (int i = 0; i < 5; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, process, &thread_ids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy mutex
    pthread_mutex_destroy(&lock);

    printf("Final Counter Value: %d\n", counter);
    return 0;
}


