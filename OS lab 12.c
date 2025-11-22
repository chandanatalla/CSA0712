#include <stdio.h>
#include <windows.h>

#define NUM_PHILOSOPHERS 5

HANDLE forks[NUM_PHILOSOPHERS];

// Philosopher thread function
DWORD WINAPI philosopher(void *arg) {
    int id = (int)(long)arg;
    int left = id;                         // left fork index
    int right = (id + 1) % NUM_PHILOSOPHERS; // right fork index

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking...\n", id);
        Sleep(500);

        // Pick up left fork
        WaitForSingleObject(forks[left], INFINITE);
        printf("Philosopher %d picked up left fork %d\n", id, left);
        Sleep(200);

        // Pick up right fork
        WaitForSingleObject(forks[right], INFINITE);
        printf("Philosopher %d picked up right fork %d\n", id, right);

        // Eating
        printf("Philosopher %d is eating...\n", id);
        Sleep(500);

        // Put down forks
        ReleaseMutex(forks[left]);
        ReleaseMutex(forks[right]);

        printf("Philosopher %d put down forks\n", id);

        Sleep(300);
    }

    return 0;
}

int main() {
    HANDLE threads[NUM_PHILOSOPHERS];
    int i;

    // Create a mutex for each fork
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        forks[i] = CreateMutex(NULL, FALSE, NULL);
    }

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        threads[i] = CreateThread(NULL, 0, philosopher, (void*)(long)i, 0, NULL);
    }

    // Let philosophers run forever
    WaitForMultipleObjects(NUM_PHILOSOPHERS, threads, TRUE, INFINITE);

    return 0;
}

