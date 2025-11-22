#include <stdio.h>
#include <stdlib.h>

int main() {
    int choice;
    char fileName[50], newFile[50];
    FILE *fp, *fp2;
    char ch;

    printf("1. Create\t2. Copy\t\t3. Delete\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter file name to create: ");
            scanf("%s", fileName);

            fp = fopen(fileName, "w");
            if (fp == NULL) {
                printf("Error creating file!\n");
                return 0;
            }
            printf("file created successfully\n");
            fclose(fp);
            break;

        case 2:
            printf("Enter file name to copy: ");
            scanf("%s", fileName);

            fp = fopen(fileName, "r");
            if (fp == NULL) {
                printf("Source file does not exist!\n");
                return 0;
            }

            printf("Enter new file name: ");
            scanf("%s", newFile);

            fp2 = fopen(newFile, "w");
            while ((ch = fgetc(fp)) != EOF) {
                fputc(ch, fp2);
            }
            fclose(fp);
            fclose(fp2);

            printf("file copied successfully\n");
            break;

        case 3:
            printf("Enter file name to delete: ");
            scanf("%s", fileName);

            if (remove(fileName) == 0)
                printf("file deleted successfully\n");
            else
                printf("Error deleting file! (File may not exist)\n");
            break;

        default:
            printf("Invalid option\n");
    }

    printf("-------------------------------\n");
    return 0;
}

