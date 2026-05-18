#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int at;
    int bt;
    int ct, tat, wt;
} Process;

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d AT, BT: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    // Sort by AT
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].at > p[j + 1].at) {
                Process temp = p[j]; p[j] = p[j + 1]; p[j + 1] = temp;
            }

    int current_time = 0;
    float avg_wt = 0, avg_tat = 0;

    printf("\n--- FCFS Scheduling ---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].at) current_time = p[i].at;
        current_time += p[i].bt;
        p[i].ct = current_time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);
    printf("Average Turnaround Time: %.2f\n", avg_tat / n);

    return 0;
}
