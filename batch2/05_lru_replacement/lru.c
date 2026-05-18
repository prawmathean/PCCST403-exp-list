#include <stdio.h>
#include <stdlib.h>

void lru(int ref[], int n, int f) {
    int frames[f], last_used[f], faults = 0;
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        last_used[i] = 0;
    }

    printf("\nLRU Page Replacement (Batch 2):\n");
    printf("Reference\tFrames\n");
    for (int i = 0; i < n; i++) {
        int found = -1;
        for (int j = 0; j < f; j++) {
            if (frames[j] == ref[i]) {
                found = j;
                break;
            }
        }

        if (found == -1) {
            int min = 0;
            for (int j = 1; j < f; j++) {
                if (last_used[j] < last_used[min]) min = j;
            }
            frames[min] = ref[i];
            last_used[min] = i + 1;
            faults++;
            printf("%d\t\t", ref[i]);
            for (int j = 0; j < f; j++) {
                if (frames[j] != -1) printf("%d ", frames[j]);
                else printf("- ");
            }
            printf("(Fault)\n");
        } else {
            last_used[found] = i + 1;
            printf("%d\t\t", ref[i]);
            for (int j = 0; j < f; j++) {
                if (frames[j] != -1) printf("%d ", frames[j]);
                else printf("- ");
            }
            printf("\n");
        }
    }
    printf("\nTotal LRU Page Faults: %d\n", faults);
}

int main() {
    int n, f;
    printf("Enter number of references: ");
    scanf("%d", &n);
    printf("Enter number of frames: ");
    scanf("%d", &f);
    int ref[n];
    printf("Enter reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &ref[i]);

    lru(ref, n, f);
    return 0;
}
