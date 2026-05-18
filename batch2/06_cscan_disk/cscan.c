#include <stdio.h>
#include <stdlib.h>

void cscan(int requests[], int n, int head, int disk_size) {
    int total_movement = 0, current = head;
    
    // Sort requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int start_idx = 0;
    while (start_idx < n && requests[start_idx] < head) start_idx++;

    printf("\nC-SCAN Sequence: %d", head);
    
    // Service from head to the end of the disk
    for (int i = start_idx; i < n; i++) {
        total_movement += abs(requests[i] - current);
        current = requests[i];
        printf(" -> %d", current);
    }
    
    // Move head to the very end
    total_movement += abs((disk_size - 1) - current);
    current = disk_size - 1;
    printf(" -> %d", current);

    // Jump to the beginning of the disk (Circular)
    printf(" -> 0");
    total_movement += (disk_size - 1); // Full jump back
    current = 0;

    // Service from the beginning to the point where head started
    for (int i = 0; i < start_idx; i++) {
        total_movement += abs(requests[i] - current);
        current = requests[i];
        printf(" -> %d", current);
    }
    
    printf("\nC-SCAN Total Head Movement: %d\n", total_movement);
}

int main() {
    int head, n, disk_size = 5000;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter %d requests: ", n);
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);

    cscan(requests, n, head, disk_size);
    return 0;
}
