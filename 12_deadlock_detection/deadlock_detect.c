#include <stdio.h>

int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m], avail[m], finish[n];

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Request Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter Available Resources: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Initial step: If a process has no allocation, it's finished
    for (int i = 0; i < n; i++) {
        int has_alloc = 0;
        for (int j = 0; j < m; j++) {
            if (alloc[i][j] != 0) {
                has_alloc = 1;
                break;
            }
        }
        finish[i] = !has_alloc;
    }

    int work[m];
    for (int i = 0; i < m; i++) work[i] = avail[i];

    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > work[j])
                        break;
                }
                
                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];
                    finish[i] = 1;
                    changed = 1;
                }
            }
        }
    }

    int deadlocked = 0;
    printf("\nDeadlock Detection Results:\n");
    for (int i = 0; i < n; i++) {
        if (finish[i] == 0) {
            printf("Process P%d is deadlocked!\n", i);
            deadlocked = 1;
        }
    }

    if (!deadlocked)
        printf("No deadlock detected. System is in a safe state.\n");
    else
        printf("System is currently in a DEADLOCK.\n");

    return 0;
}
