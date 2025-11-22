#include <stdio.h>

int main() {
    int n, i, j;
    int bt[20], wt[20], tat[20], p[20];
    float avg_wt = 0, avg_tat = 0;
    int temp;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input burst times
    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d Burst Time: ", i+1);
        scanf("%d", &bt[i]);
        p[i] = i + 1; // process ID
    }

    // Sort processes by burst time (SJF)
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (bt[j] > bt[j+1]) {
                // swap burst times
                temp = bt[j];
                bt[j] = bt[j+1];
                bt[j+1] = temp;

                // swap process IDs
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    // Waiting time calculation
    wt[0] = 0;
    for (i = 1; i < n; i++) {
        wt[i] = wt[i-1] + bt[i-1];
    }

    // Turnaround time calculation
    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    // Output results
    printf("\n--------------------------------------------------\n");
    printf("Process\tBurst Time\tWaiting\tTurnaround\n");
    printf("--------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\n", p[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time     = %.2f", avg_wt);
    printf("\nAverage Turnaround Time  = %.2f\n", avg_tat);

    return 0;
}

