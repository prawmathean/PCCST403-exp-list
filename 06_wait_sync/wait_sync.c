#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        // Child process
        // We want this to print first
        printf("PCCSL407 ");
        // Ensure it's printed immediately
        fflush(stdout); 
    } 
    else {
        // Parent process
        // Wait for child to finish printing "PCCSL407"
        wait(NULL); 
        printf("Operating Systems Lab\n");
    }

    return 0;
}
