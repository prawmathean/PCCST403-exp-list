#include <stdio.h>

/* Deadlock Detection Algorithm */
int main() {
    int n = 3, m = 3; // 3 processes, 3 resources
    int alloc[3][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 3}};
    int request[3][3] = {{0, 0, 0}, {2, 0, 2}, {0, 0, 1}};
    int avail[3] = {0, 0, 0};

    int work[3], finish[3] = {0};
    for(int i=0; i<m; i++) work[i] = avail[i];

    // Detection loop
    for(int k=0; k<n; k++) {
        for(int i=0; i<n; i++) {
            if(!finish[i]) {
                int possible = 1;
                for(int j=0; j<m; j++) {
                    if(request[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }
                if(possible) {
                    for(int j=0; j<m; j++) work[j] += alloc[i][j];
                    finish[i] = 1;
                }
            }
        }
    }

    int deadlocked = 0;
    for(int i=0; i<n; i++) {
        if(!finish[i]) {
            if(!deadlocked) printf("Deadlock detected! Processes involved: ");
            printf("P%d ", i);
            deadlocked = 1;
        }
    }

    if(!deadlocked) printf("No deadlock detected.\n");
    else printf("\n");

    return 0;
}
