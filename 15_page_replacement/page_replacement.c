#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fifo(int ref[], int n, int f) {
    int frames[f], count = 0, faults = 0, next = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;

    printf("\nFIFO Strategy:\nReference\tFrames\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (frames[j] == ref[i]) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            frames[next] = ref[i];
            next = (next + 1) % f;
            faults++;
            printf("%d\t\t", ref[i]);
            for (int j = 0; j < f; j++) printf("%d ", frames[j]);
            printf("(Fault)\n");
        } else {
            printf("%d\t\t", ref[i]);
            for (int j = 0; j < f; j++) printf("%d ", frames[j]);
            printf("\n");
        }
    }
    printf("Total FIFO Page Faults: %d\n", faults);
}

void lru(int ref[], int n, int f) {
    int frames[f], last_used[f], faults = 0;
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        last_used[i] = 0;
    }

    printf("\nLRU Strategy:\nReference\tFrames\n");
    for (int i = 0; i < n; i++) {
        int found = -1;
        for (int j = 0; j < f; j++) {
            if (frames[j] == ref[i]) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            // Find Least Recently Used frame
            int min = 0;
            for (int j = 1; j < f; j++) {
                if (last_used[j] < last_used[min]) min = j;
            }
            frames[min] = ref[i];
            last_used[min] = i + 1;
            faults++;
            printf("%d\t\t", ref[i]);
            for (int j = 0; j < f; j++) printf("%d ", frames[j]);
            printf("(Fault)\n");
        } else {
            last_used[found] = i + 1; // Update last used time
            printf("%d\t\t", ref[i]);
            for (int j = 0; j < f; j++) printf("%d ", frames[j]);
            printf("\n");
        }
    }
    printf("Total LRU Page Faults: %d\n", faults);
}

int main() {
    int n, f;
    printf("Enter number of references: ");
    scanf("%d", &n);
    printf("Enter number of frames: ");
    scanf("%d", &f);

    int ref[n];
    srand(time(NULL));
    printf("Generated Reference String: ");
    for (int i = 0; i < n; i++) {
        ref[i] = rand() % 10;
        printf("%d ", ref[i]);
    }
    printf("\n");

    fifo(ref, n, f);
    lru(ref, n, f);

    return 0;
}
