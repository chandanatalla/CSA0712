#include <stdio.h>
#include <windows.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    printf("Parent Process:\n");
    printf("PID = %lu\n", GetCurrentProcessId());

    // Create a new process (child)
    if (CreateProcess(
            NULL,               // No module name
            "notepad.exe",      // Program to run (child process)
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi)) 
    {
        printf("Child Process Created!\n");
        printf("Child PID = %lu\n", pi.dwProcessId);
    }
    else {
        printf("Process creation failed! Error: %lu\n", GetLastError());
    }

    return 0;
}

