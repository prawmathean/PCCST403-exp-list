#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>

void heavy_computation() {
    printf("Doing some work...\n");
    for (long i = 0; i < 100000000; i++); // Just a loop to consume time
}

int main() {
    struct tms cpu_times;
    clock_t start_time, end_time;
    long ticks_per_sec = sysconf(_SC_CLK_TCK);

    printf("Current System Time: %ld\n", time(NULL));

    heavy_computation();

    // Although the aim mentions /proc, in C we usually use times() 
    // which internally gets info from the kernel (similar to /proc/self/stat)
    times(&cpu_times);

    printf("\nExecution Times (in clock ticks):\n");
    printf("User Mode Time: %ld ticks\n", cpu_times.tms_utime);
    printf("Kernel Mode Time: %ld ticks\n", cpu_times.tms_stime);

    printf("\nExecution Times (in seconds):\n");
    printf("User Mode Time: %.4f sec\n", (double)cpu_times.tms_utime / ticks_per_sec);
    printf("Kernel Mode Time: %.4f sec\n", (double)cpu_times.tms_stime / ticks_per_sec);

    return 0;
}
