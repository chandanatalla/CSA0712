
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char buffer[100];

    // 1. Create and write to a file
    fp = fopen("file_demo.txt", "w");
    if (fp == NULL) {
        perror("Error creating file");
        return 1;
    }
    fprintf(fp, "Hello, this is a demo file.\n");
    fprintf(fp, "Second line of text.\n");
    fclose(fp);
    printf("File created and written successfully.\n");

    // 2. Read from the file
    fp = fopen("file_demo.txt", "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return 1;
    }
    printf("Contents of file_demo.txt:\n");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    fclose(fp);

    // 3. Append to the file
    fp = fopen("file_demo.txt", "a");
    if (fp == NULL) {
        perror("Error opening file for appending");
        return 1;
    }
    fprintf(fp, "Appended line at the end.\n");
    fclose(fp);
    printf("\nData appended successfully.\n");

    // 4. Read again to confirm append
    fp = fopen("file_demo.txt", "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return 1;
    }
    printf("\nUpdated contents of file_demo.txt:\n");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    fclose(fp);

    // 5. Delete the file
    if (remove("file_demo.txt") == 0) {
        printf("\nFile deleted successfully.\n");
    } else {
        perror("Error deleting file");
    }

    return 0;
}


