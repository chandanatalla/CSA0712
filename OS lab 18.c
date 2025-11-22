
#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty = 10; // buffer size
int item = 0;

void wait(int *s) {
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void producer() {
    wait(&mutex);
    if (empty != 0) {
        signal(&full);
        wait(&empty);
        item++;
        printf("Producer produces item %d\n", item);
    } else {
        printf("Buffer is full! Producer cannot produce.\n");
    }
    signal(&mutex);
}

void consumer() {
    wait(&mutex);
    if (full != 0) {
        signal(&empty);
        wait(&full);
        printf("Consumer consumes item %d\n", item);
        item--;
    } else {
        printf("Buffer is empty! Consumer cannot consume.\n");
    }
    signal(&mutex);
}

int main() {
    int choice;
    printf("\nProducer-Consumer Problem using Semaphores\n");
    while (1) {
        printf("\n1. Produce\n2. Consume\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                producer();
                break;
            case 2:
                consumer();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}





