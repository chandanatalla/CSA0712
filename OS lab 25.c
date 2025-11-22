
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>      // open, O_* flags
#include <unistd.h>     // read, write, lseek, close
#include <sys/stat.h>   // stat
#include <dirent.h>     // opendir, readdir

int main() {
    int fd;
    char buffer[100];
    struct stat fileStat;

    // 1. Open a file (create if not exists)
    fd = open("test.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    printf("File opened successfully with descriptor %d\n", fd);

    // 2. Write to the file
    const char *text = "Hello from OS Lab!\n";
    write(fd, text, strlen(text));

    // 3. Seek back to beginning
    lseek(fd, 0, SEEK_SET);

    // 4. Read from the file
    int bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    buffer[bytesRead] = '\0';
    printf("Data read from file: %s\n", buffer);

    // 5. Get file information using stat
    if (stat("test.txt", &fileStat) < 0) {
        perror("Error getting file stats");
        return 1;
    }
    printf("File size: %ld bytes\n", fileStat.st_size);

    close(fd);

    // 6. Open a directory and list files
    DIR *dir;
    struct dirent *entry;
    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }
    printf("Files in current directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("  %s\n", entry->d_name);
    }
    closedir(dir);

    return 0;
}


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

