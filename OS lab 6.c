#include <stdio.h>

int main() {
    int n, i, tq, remaining;
    int bt[20], rt[20], wt[20], tat[20];
    int time = 0;  // current time

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input burst times
    for (i = 0; i < n; i++) {
        printf("Enter Burst Time for Process P%d: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];   // remaining time initially same as burst time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    remaining = n;

    // Initialize waiting and TAT arrays
    for (i = 0; i < n; i++) {
        wt[i] = tat[i] = 0;
    }

    // Round Robin simulation
    while (remaining != 0) {
        for (i = 0; i < n; i++) {
            if (rt[i] > 0) {
                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    wt[i] = time - bt[i];
                    rt[i] = 0;
                    remaining--;
                }
            }
        }
    }

    // Turnaround time
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }

    // Display Results
    printf("\n----------------------------------------------\n");
    printf("Process\tBurst\tWaiting\tTurnaround\n");
    printf("----------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n", i+1, bt[i], wt[i], tat[i]);
    }

    // Average Times
    float avg_wt = 0, avg_tat = 0;
    for (i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}

