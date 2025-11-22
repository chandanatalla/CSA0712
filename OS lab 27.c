
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>   // for directory operations
#include <sys/stat.h> // for file info
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    // Open current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    printf("Listing files (simulating ls command):\n\n");

    while ((entry = readdir(dir)) != NULL) {
        // Get file info
        if (stat(entry->d_name, &fileStat) == 0) {
            if (S_ISDIR(fileStat.st_mode)) {
                printf("[DIR]  %s\n", entry->d_name);
            } else {
                printf("[FILE] %s\t(%ld bytes)\n", entry->d_name, fileStat.st_size);
            }
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}


