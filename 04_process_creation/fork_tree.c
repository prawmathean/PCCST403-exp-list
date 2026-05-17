#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/* Simple fork demo to show parent-child relationship */
int main() {
    pid_t p;
    
    printf("Before fork, PID is %d\n", getpid());
    
    p = fork();

    if (p < 0) {
        printf("Fork failed!\n");
    } 
    else if (p == 0) {
        // This block runs in the child process
        printf("I am the CHILD process (PID: %d, Parent PID: %d)\n", getpid(), getppid());
    } 
    else {
        // This block runs in the parent process
        printf("I am the PARENT process (PID: %d, My Child is: %d)\n", getpid(), p);
        sleep(1); // Give child time to print
    }

    return 0;
}
