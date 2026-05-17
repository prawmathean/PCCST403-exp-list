#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/* Using execvp to run another program */
int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child: About to run 'ls -l' using execvp...\n");
        
        // Arguments for the command
        char *args[] = {"ls", "-l", NULL};
        
        // execvp replaces the current process image
        execvp(args[0], args);
        
        // If execvp returns, it failed
        perror("execvp failed");
    } 
    else {
        wait(NULL); // Wait for child to finish
        printf("Parent: Child process has finished execution.\n");
    }

    return 0;
}
/* 
   Note: To run a custom "myadder" program, you would replace "ls" 
   with "./myadder" and provide its arguments in the args array.
*/
