#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int at, bt, priority;
    int ct, tat, wt;
    int finished;
} Process;

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d AT, BT, Priority (Higher number = Higher Priority): ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].finished = 0;
    }

    int current_time = 0, completed = 0;
    float avg_wt = 0, avg_tat = 0;

    printf("\n--- Non-Preemptive Priority Scheduling ---\n");
    printf("PID\tAT\tBT\tPRI\tCT\tTAT\tWT\n");

    while (completed < n) {
        int idx = -1;
        int max_priority = -1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && !p[i].finished) {
                if (p[i].priority > max_priority) {
                    max_priority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            current_time++;
        } else {
            current_time += p[idx].bt;
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].finished = 1;
            completed++;

            avg_wt += p[idx].wt;
            avg_tat += p[idx].tat;
            printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[idx].pid, p[idx].at, p[idx].bt, p[idx].priority, p[idx].ct, p[idx].tat, p[idx].wt);
        }
    }

    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);
    printf("Average Turnaround Time: %.2f\n", avg_tat / n);

    return 0;
}
