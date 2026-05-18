#include <stdio.h>

int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m], need[n][m];

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("Enter Available Resources: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    int finish[n], safe_seq[n], count = 0;
    for (int i = 0; i < n; i++) finish[i] = 0;

    // Safety Algorithm
    int work[m];
    for (int i = 0; i < m; i++) work[i] = avail[i];

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j])
                        break;
                }
                
                if (j == m) {
                    // Process can be finished
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];
                    safe_seq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                    printf("Process P%d is added to safe sequence.\n", i);
                }
            }
        }
        if (found == 0) {
            printf("\nSystem is NOT in a safe state!\n");
            return 0;
        }
    }

    printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safe_seq[i]);
    printf("\n");

    return 0;
}
