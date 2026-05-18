#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    char n1[10], n2[10];
    pid_t pid;

    printf("Enter two integers to add: ");
    scanf("%s %s", n1, n2);

    pid = fork();

    if (pid < 0) {
        perror("Fork Failed");
        exit(1);
    } 
    else if (pid == 0) {
        // Child process
        printf("Child (PID: %d) replacing image with 'myadder'...\n", getpid());
        
        // Arguments for execvp: program name, arg1, arg2, and NULL
        char *args[] = {"./myadder", n1, n2, NULL};
        
        if (execvp(args[0], args) == -1) {
            perror("Execvp Failed (Make sure 'myadder' is compiled!)");
            exit(1);
        }
    } 
    else {
        // Parent process
        wait(NULL);
        printf("\nParent: Child has finished adding numbers.\n");
    }

    return 0;
}
