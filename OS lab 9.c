#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hMapFile;
    char *buffer;

    // Create shared memory of size 1024 bytes
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        1024,
        "MySharedMemory"
    );

    if (hMapFile == NULL) {
        printf("Could not create shared memory.\n");
        return 1;
    }

    buffer = (char*) MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0, 0, 1024
    );

    if (buffer == NULL) {
        printf("Could not map shared memory.\n");
        CloseHandle(hMapFile);
        return 1;
    }

    printf("Enter message to write into shared memory:\n");
    gets(buffer);

    printf("Data written. Run reader program now.\n");

    printf("Press Enter to exit...");
    getchar();

    UnmapViewOfFile(buffer);
    CloseHandle(hMapFile);
    return 0;
}



