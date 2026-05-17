#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/* Parent waiting for child to finish to ensure order */
int main() {
    pid_t p = fork();

    if (p == 0) {
        printf("Child: I'm starting some work...\n");
        sleep(2); // Simulate work
        printf("Child: Work done, exiting now.\n");
    } 
    else {
        printf("Parent: Waiting for my child to finish...\n");
        wait(NULL); // Strict synchronization
        printf("Parent: Child is done, now I can finish too.\n");
    }

    return 0;
}
