#include <stdio.h>
#include <stdlib.h>

/* Simple program to run some linux commands we use in the lab */
int main() {
    printf("--- My Linux Command Helper ---\n");

    // We can just use system() to run these directly from C
    printf("\n1. File type of this source:\n");
    system("file linux_cmd.c");

    printf("\n2. First few strings in the file:\n");
    system("strings linux_cmd.c | head -n 3");

    printf("\n3. Hex dump (first 2 lines):\n");
    system("xxd linux_cmd.c | head -n 2");

    printf("\n4. Current processes (short list):\n");
    system("ps | head -n 5");

    printf("\n5. System uptime and load:\n");
    system("uptime");

    printf("\n6. Memory usage summary:\n");
    system("free -h");

    printf("\nDone executing commands!\n");
    return 0;
}
