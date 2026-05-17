#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Reading system info directly from the /proc filesystem */
int main() {
    FILE *fp;
    char line[256];

    printf("--- Machine Info from /proc ---\n\n");

    // Get CPU model
    fp = fopen("/proc/cpuinfo", "r");
    while (fgets(line, 256, fp)) {
        if (strncmp(line, "model name", 10) == 0) {
            printf("CPU: %s", strchr(line, ':') + 2);
            break;
        }
    }
    fclose(fp);

    // Get Memory info
    fp = fopen("/proc/meminfo", "r");
    while (fgets(line, 256, fp)) {
        if (strncmp(line, "MemTotal", 8) == 0) printf("%s", line);
        if (strncmp(line, "MemFree", 7) == 0) printf("%s", line);
    }
    fclose(fp);

    // Get Process stats
    fp = fopen("/proc/stat", "r");
    while (fgets(line, 256, fp)) {
        if (strncmp(line, "procs_running", 13) == 0) printf("Running processes: %s", strchr(line, ' ') + 1);
        if (strncmp(line, "procs_blocked", 13) == 0) printf("Blocked processes: %s", strchr(line, ' ') + 1);
    }
    fclose(fp);

    return 0;
}
