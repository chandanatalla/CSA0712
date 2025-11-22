// multithread_compat.c
#include <stdio.h>
#include <windows.h>

DWORD WINAPI threadFunc1(LPVOID arg) {
    int i;                       // declare loop var here (C89 compatible)
    for (i = 1; i <= 5; i++) {
        printf("Thread 1: Count %d\n", i);
        fflush(stdout);
        Sleep(300);
    }
    return 0;
}

DWORD WINAPI threadFunc2(LPVOID arg) {
    int i;                       // declare loop var here too
    for (i = 1; i <= 5; i++) {
        printf("Thread 2: Count %d\n", i);
        fflush(stdout);
        Sleep(300);
    }
    return 0;
}

int main(void) {
    HANDLE t1 = NULL, t2 = NULL;
    DWORD id1 = 0, id2 = 0;

    t1 = CreateThread(NULL, 0, threadFunc1, NULL, 0, &id1);
    if (t1 == NULL) {
        fprintf(stderr, "CreateThread failed for t1 (error %lu)\n", GetLastError());
        return 1;
    }

    t2 = CreateThread(NULL, 0, threadFunc2, NULL, 0, &id2);
    if (t2 == NULL) {
        fprintf(stderr, "CreateThread failed for t2 (error %lu)\n", GetLastError());
        CloseHandle(t1);
        return 1;
    }

    WaitForSingleObject(t1, INFINITE);
    WaitForSingleObject(t2, INFINITE);

    CloseHandle(t1);
    CloseHandle(t2);

    return 0;
}


