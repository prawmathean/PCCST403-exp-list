#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_cpu_cores() {
    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (!fp) return;
    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "processor", 9) == 0) count++;
    }
    printf("Number of CPU cores: %d\n", count);
    fclose(fp);
}

void get_mem_info() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) return;
    char line[256];
    long total = 0, free = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "MemTotal:", 9) == 0) sscanf(line, "MemTotal: %ld", &total);
        if (strncmp(line, "MemFree:", 8) == 0) sscanf(line, "MemFree: %ld", &free);
    }
    printf("Total Memory: %ld KB\n", total);
    printf("Free Memory Fraction: %.2f%%\n", ((float)free / total) * 100);
    fclose(fp);
}

void get_proc_stats() {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) return;
    char line[256];
    long forks = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "processes", 9) == 0) sscanf(line, "processes %ld", &forks);
    }
    printf("Processes forked since last bootup: %ld\n", forks);
    fclose(fp);
    
    // For running/blocked, we can check /proc/loadavg or count in /proc/stat
    fp = fopen("/proc/loadavg", "r");
    if (fp) {
        int running, total;
        fscanf(fp, "%*f %*f %*f %d/%d", &running, &total);
        printf("Processes currently running: %d\n", running);
        printf("Total processes currently existing: %d\n", total);
        fclose(fp);
    }
}

int main(int argc, char *argv[]) {
    printf("--- Machine Information ---\n");
    get_cpu_cores();
    get_mem_info();
    get_proc_stats();

    if (argc > 1) {
        // Part (f): Context switches for a specific PID
        char path[64];
        sprintf(path, "/proc/%s/status", argv[1]);
        FILE *fp = fopen(path, "r");
        if (fp) {
            char line[256];
            long switches = 0;
            while (fgets(line, sizeof(line), fp)) {
                if (strstr(line, "ctxt_switches")) {
                    long val;
                    sscanf(strchr(line, ':') + 1, "%ld", &val);
                    switches += val;
                }
            }
            printf("Context switches for PID %s: %ld\n", argv[1], switches);
            fclose(fp);
        } else {
            printf("Could not find status for PID %s\n", argv[1]);
        }
    } else {
        printf("\nTip: Run with a PID as argument to see context switches (e.g., ./a.out 1)\n");
    }

    return 0;
}
