#include <stdio.h>
#include <stdlib.h>

void sstf(int requests[], int n, int head) {
    int total_movement = 0, current = head;
    int serviced[n];
    for (int i = 0; i < n; i++) serviced[i] = 0;

    printf("\nSSTF Sequence: %d", head);
    for (int i = 0; i < n; i++) {
        int min_dist = 1e9, index = -1;
        for (int j = 0; j < n; j++) {
            if (!serviced[j]) {
                int dist = abs(requests[j] - current);
                if (dist < min_dist) {
                    min_dist = dist;
                    index = j;
                }
            }
        }
        serviced[index] = 1;
        total_movement += min_dist;
        current = requests[index];
        printf(" -> %d", current);
    }
    printf("\nSSTF Total Head Movement: %d\n", total_movement);
}

void look(int requests[], int n, int head) {
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

    // Find the starting point in the sorted array
    int start_idx = 0;
    while (start_idx < n && requests[start_idx] < head) start_idx++;

    printf("\nLOOK Sequence (Direction: Increasing): %d", head);
    
    // Service to the right
    for (int i = start_idx; i < n; i++) {
        total_movement += abs(requests[i] - current);
        current = requests[i];
        printf(" -> %d", current);
    }
    
    // Service to the left
    for (int i = start_idx - 1; i >= 0; i--) {
        total_movement += abs(requests[i] - current);
        current = requests[i];
        printf(" -> %d", current);
    }
    
    printf("\nLOOK Total Head Movement: %d\n", total_movement);
}

int main() {
    int head, n = 10;
    int requests[10];

    printf("Initial Disk Head Position: ");
    scanf("%d", &head);

    printf("Enter 10 cylinder requests (0-4999): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    sstf(requests, n, head);
    look(requests, n, head);

    return 0;
}
