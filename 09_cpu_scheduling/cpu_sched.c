#include <stdio.h>
#include <stdlib.h>

/* CPU Scheduling: FCFS, SRTF, Priority, Round Robin */

struct Process {
    int id, at, bt, priority, wt, tat, remaining_bt;
};

void reset(struct Process p[], int n) {
    for(int i=0; i<n; i++) {
        p[i].wt = p[i].tat = 0;
        p[i].remaining_bt = p[i].bt;
    }
}

void print_stats(struct Process p[], int n, char* name) {
    float avg_wt = 0, avg_tat = 0;
    printf("\n--- %s ---\nID\tWT\tTAT\n", name);
    for(int i=0; i<n; i++) {
        avg_wt += p[i].wt; avg_tat += p[i].tat;
        printf("%d\t%d\t%d\n", p[i].id, p[i].wt, p[i].tat);
    }
    printf("Avg WT: %.2f, Avg TAT: %.2f\n", avg_wt/n, avg_tat/n);
}

void fcfs(struct Process p[], int n) {
    int time = 0;
    for(int i=0; i<n; i++) {
        if (time < p[i].at) time = p[i].at;
        p[i].wt = time - p[i].at;
        time += p[i].bt;
        p[i].tat = time - p[i].at;
    }
    print_stats(p, n, "FCFS");
}

void round_robin(struct Process p[], int n, int q) {
    reset(p, n);
    int time = 0, completed = 0;
    while(completed < n) {
        int flag = 0;
        for(int i=0; i<n; i++) {
            if(p[i].remaining_bt > 0 && p[i].at <= time) {
                flag = 1;
                if(p[i].remaining_bt > q) {
                    time += q;
                    p[i].remaining_bt -= q;
                } else {
                    time += p[i].remaining_bt;
                    p[i].wt = time - p[i].at - p[i].bt;
                    p[i].tat = time - p[i].at;
                    p[i].remaining_bt = 0;
                    completed++;
                }
            }
        }
        if(!flag) time++;
    }
    print_stats(p, n, "Round Robin (q=3)");
}

// Simple Priority (Non-preemptive)
void priority_sched(struct Process p[], int n) {
    reset(p, n);
    int time = 0, completed = 0, visited[10] = {0};
    while(completed < n) {
        int idx = -1, min_prio = 9999;
        for(int i=0; i<n; i++) {
            if(!visited[i] && p[i].at <= time && p[i].priority < min_prio) {
                min_prio = p[i].priority;
                idx = i;
            }
        }
        if(idx != -1) {
            p[idx].wt = time - p[idx].at;
            time += p[idx].bt;
            p[idx].tat = time - p[idx].at;
            visited[idx] = 1;
            completed++;
        } else time++;
    }
    print_stats(p, n, "Priority (Non-Preemptive)");
}

int main() {
    int n = 3;
    struct Process p[] = {
        {1, 0, 10, 2, 0, 0, 10},
        {2, 1, 5, 1, 0, 0, 5},
        {3, 2, 8, 3, 0, 0, 8}
    };
    fcfs(p, n);
    priority_sched(p, n);
    round_robin(p, n, 3);
    return 0;
}
