#include <stdio.h>
#include <stdlib.h>

/* Disk Scheduling: SSTF, LOOK, C-SCAN */

int compare(const void *a, const void *b) { return (*(int*)a - *(int*)b); }

void sstf(int req[], int n, int head) {
    int total = 0, visited[20] = {0};
    int curr = head;
    for(int i=0; i<n; i++) {
        int min = 9999, idx = -1;
        for(int j=0; j<n; j++) {
            if(!visited[j] && abs(req[j] - curr) < min) {
                min = abs(req[j] - curr);
                idx = j;
            }
        }
        visited[idx] = 1;
        total += min;
        curr = req[idx];
    }
    printf("SSTF Total Movement: %d\n", total);
}

void cscan(int req[], int n, int head, int size) {
    int total = 0, q[22], m=0;
    for(int i=0; i<n; i++) q[m++] = req[i];
    q[m++] = 0; q[m++] = size - 1;
    qsort(q, m, sizeof(int), compare);
    
    int idx = 0;
    while(q[idx] < head) idx++;
    
    // Go right to end
    total += (size - 1 - head);
    // Jump to 0
    total += (size - 1);
    // Go to last request before head
    total += q[idx-1];
    
    printf("C-SCAN Total Movement: %d\n", total);
}

int main() {
    int req[] = {98, 183, 37, 122, 14, 124, 65, 67};
    int n = 8, head = 53, size = 200;
    sstf(req, n, head);
    cscan(req, n, head, size);
    return 0;
}
