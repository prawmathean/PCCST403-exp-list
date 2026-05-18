#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int at;
    int bt;
    int priority;
    int remaining_bt;
    int ct, tat, wt;
} Process;

void reset_processes(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].remaining_bt = p[i].bt;
        p[i].ct = p[i].tat = p[i].wt = 0;
    }
}

void print_metrics(Process p[], int n, char *algo) {
    float avg_wt = 0, avg_tat = 0;
    printf("\n--- %s ---\n", algo);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }
    printf("Average Waiting Time: %.2f\n", avg_wt / n);
    printf("Average Turnaround Time: %.2f\n", avg_tat / n);
}

void fcfs(Process p[], int n) {
    int current_time = 0;
    // Sort by AT for FCFS
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].at > p[j + 1].at) {
                Process temp = p[j]; p[j] = p[j + 1]; p[j + 1] = temp;
            }

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].at) current_time = p[i].at;
        current_time += p[i].bt;
        p[i].ct = current_time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
    print_metrics(p, n, "FCFS");
}

void rr(Process orig_p[], int n, int quantum) {
    Process p[n];
    for (int i = 0; i < n; i++) p[i] = orig_p[i];
    reset_processes(p, n);
    
    int current_time = 0, completed = 0;
    while (completed < n) {
        int flag = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_bt > 0 && p[i].at <= current_time) {
                flag = 1;
                if (p[i].remaining_bt > quantum) {
                    current_time += quantum;
                    p[i].remaining_bt -= quantum;
                } else {
                    current_time += p[i].remaining_bt;
                    p[i].remaining_bt = 0;
                    p[i].ct = current_time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    completed++;
                }
            }
        }
        if (flag == 0) current_time++;
    }
    print_metrics(p, n, "Round Robin");
}

int main() {
    int n, q;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P%d AT, BT, Priority: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
    }
    printf("Enter Time Quantum for RR: ");
    scanf("%d", &q);

    fcfs(p, n);
    rr(p, n, q);
    
    printf("\nNote: SRTF and Non-Preemptive Priority follow similar logic using a ready queue with different sorting criteria.\n");
    return 0;
}
