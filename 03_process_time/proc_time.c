#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>

/* Calculating time spent in user vs kernel mode */
int main() {
    struct tms start_t, end_t;
    clock_t start_clock, end_clock;
    long ticks = sysconf(_SC_CLK_TCK);

    start_clock = times(&start_t);

    printf("Calculating something heavy...\n");
    for (volatile long i = 0; i < 100000000; i++); // Dummy loop

    end_clock = times(&end_t);

    printf("\nTime Analysis:\n");
    printf("User Mode:   %.4f sec\n", (double)(end_t.tms_utime - start_t.tms_utime) / ticks);
    printf("Kernel Mode: %.4f sec\n", (double)(end_t.tms_stime - start_t.tms_stime) / ticks);
    printf("Total (Real):%.4f sec\n", (double)(end_clock - start_clock) / ticks);

    return 0;
}
