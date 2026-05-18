#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    printf("Parent Process (PID: %d) is about to fork...\n", getpid());

    pid = fork();

    if (pid < 0) {
        // Error occurred
        fprintf(stderr, "Fork Failed\n");
        return 1;
    } 
    else if (pid == 0) {
        // Child process
        printf("I am the Child Process!\n");
        printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
        
        // Show process tree starting from this child
        printf("\nProcess Tree for Child:\n");
        char cmd[50];
        sprintf(cmd, "pstree -p %d", getpid());
        system(cmd);
        
        printf("\nChild process finished.\n");
    } 
    else {
        // Parent process
        // wait(NULL) makes the parent wait for the child to finish
        wait(NULL); 
        printf("I am the Parent Process (PID: %d).\n", getpid());
        printf("My child has finished execution.\n");
    }

    return 0;
}
