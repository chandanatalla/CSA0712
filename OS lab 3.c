#include <stdio.h>

int main() {
    int n, i;
    int bt[20], wt[20], tat[20];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input burst times
    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d Burst Time: ", i+1);
        scanf("%d", &bt[i]);
    }

    // FCFS calculations
    wt[0] = 0;  // first process has 0 waiting time

    for (i = 1; i < n; i++) {
        wt[i] = wt[i-1] + bt[i-1];
    }

    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    // Output
    printf("\n-----------------------------------------\n");
    printf("Process\tBurst Time\tWaiting\tTurnaround\n");
    printf("-----------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\n", i+1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time     = %.2f", avg_wt);
    printf("\nAverage Turnaround Time  = %.2f\n", avg_tat);

    return 0;
}

