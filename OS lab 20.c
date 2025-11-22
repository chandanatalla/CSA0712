
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

HANDLE mutex;       // Controls access to readCount
HANDLE wrt;         // Controls access to the shared resource
int readCount = 0;  // Number of active readers

DWORD WINAPI reader(LPVOID param) {
    WaitForSingleObject(mutex, INFINITE);
    readCount++;
    if (readCount == 1)
        WaitForSingleObject(wrt, INFINITE); // First reader locks writer
    ReleaseMutex(mutex);

    printf("Reader %d is reading...\n", *((int*)param));
    Sleep(1000); // Simulate reading

    WaitForSingleObject(mutex, INFINITE);
    readCount--;
    if (readCount == 0)
        ReleaseMutex(wrt); // Last reader unlocks writer
    ReleaseMutex(mutex);

    return 0;
}

DWORD WINAPI writer(LPVOID param) {
    WaitForSingleObject(wrt, INFINITE);
    printf("Writer %d is writing...\n", *((int*)param));
    Sleep(1500); // Simulate writing
    ReleaseMutex(wrt);
    return 0;
}

int main() {
    int i;
    int readerIds[3] = {1, 2, 3};
    int writerIds[2] = {1, 2};

    mutex = CreateMutex(NULL, FALSE, NULL);
    wrt = CreateMutex(NULL, FALSE, NULL);

    HANDLE rThreads[3], wThreads[2];

    for (i = 0; i < 3; i++)
        rThreads[i] = CreateThread(NULL, 0, reader, &readerIds[i], 0, NULL);

    for (i = 0; i < 2; i++)
        wThreads[i] = CreateThread(NULL, 0, writer, &writerIds[i], 0, NULL);

    WaitForMultipleObjects(3, rThreads, TRUE, INFINITE);
    WaitForMultipleObjects(2, wThreads, TRUE, INFINITE);

    CloseHandle(mutex);
    CloseHandle(wrt);

    return 0;
}



