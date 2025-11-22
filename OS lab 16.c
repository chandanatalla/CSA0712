#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int id;
    char name[30];
    float salary;
};

int main() {

    FILE *fp;
    struct Employee emp;

    // Open or create binary file
    fp = fopen("employee.dat", "ab");   // append in binary mode
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);

    printf("Enter Employee Name: ");
    scanf("%s", emp.name);

    printf("Enter Salary: ");
    scanf("%f", &emp.salary);

    // Write employee record
    fwrite(&emp, sizeof(emp), 1, fp);

    printf("Employee added successfully.\n");

    fclose(fp);
    return 0;
}

