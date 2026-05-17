#include <stdio.h>

/* Page Replacement: FIFO, LRU, Optimal */

void fifo(int pages[], int n, int frames) {
    int frame_arr[frames], count = 0, faults = 0;
    for(int i=0; i<frames; i++) frame_arr[i] = -1;

    for(int i=0; i<n; i++) {
        int found = 0;
        for(int j=0; j<frames; j++) if(frame_arr[j] == pages[i]) found = 1;
        if(!found) {
            frame_arr[count % frames] = pages[i];
            count++;
            faults++;
        }
    }
    printf("FIFO Faults: %d\n", faults);
}

void lru(int pages[], int n, int frames) {
    int frame_arr[frames], time[frames], faults = 0;
    for(int i=0; i<frames; i++) frame_arr[i] = -1;

    for(int i=0; i<n; i++) {
        int found = 0, pos;
        for(int j=0; j<frames; j++) if(frame_arr[j] == pages[i]) { found = 1; time[j] = i; }
        if(!found) {
            int min = 9999, idx = 0;
            for(int j=0; j<frames; j++) {
                if(frame_arr[j] == -1) { idx = j; break; }
                if(time[j] < min) { min = time[j]; idx = j; }
            }
            frame_arr[idx] = pages[i];
            time[idx] = i;
            faults++;
        }
    }
    printf("LRU Faults: %d\n", faults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = 13, frames = 3;
    fifo(pages, n, frames);
    lru(pages, n, frames);
    return 0;
}
