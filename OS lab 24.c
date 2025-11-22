
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // for open() and flags
#include <unistd.h>     // for read(), write(), close()
#include <string.h>

int main() {
    int fd;
    char buffer[100];
    ssize_t bytesRead;

    // 1. Create/Open a file
    fd = open("demo24.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    printf("File opened successfully with descriptor %d\n", fd);

    // 2. Write to the file
    const char *text = "This is Program 24 demo.\n";
    if (write(fd, text, strlen(text)) == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    printf("Data written successfully.\n");

    // 3. Move file pointer to beginning
    lseek(fd, 0, SEEK_SET);

    // 4. Read from the file
    bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        perror("Error reading file");
        close(fd);
        return 1;
    }
    buffer[bytesRead] = '\0';
    printf("Data read from file: %s\n", buffer);

    // 5. Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }
    printf("File closed successfully.\n");

    return 0;
}


