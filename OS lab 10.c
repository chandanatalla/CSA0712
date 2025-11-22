#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

char messageQueue[256];   // Simple message queue buffer
int hasMessage = 0;       // Flag to indicate message availability

DWORD WINAPI producerThread(LPVOID arg) {
    char message[] = "Hello, message queue!";

    strcpy(messageQueue, message);
    hasMessage = 1;

    printf("Producer: Data sent to message queue: %s\n", message);
    return 0;
}

DWORD WINAPI consumerThread(LPVOID arg) {
    // Wait for producer to send message
    while (!hasMessage) {
        Sleep(10);
    }

    printf("Consumer: Data received from message queue: %s\n", messageQueue);
    return 0;
}

int main() {
    HANDLE producer, consumer;

    // Create producer and consumer threads
    producer = CreateThread(NULL, 0, producerThread, NULL, 0, NULL);
    consumer = CreateThread(NULL, 0, consumerThread, NULL, 0, NULL);

    // Wait for both threads to finish
    WaitForSingleObject(producer, INFINITE);
    WaitForSingleObject(consumer, INFINITE);

    CloseHandle(producer);
    CloseHandle(consumer);

    return 0;
}

