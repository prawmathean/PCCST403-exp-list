#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int fd[2]; // fd[0] for read, fd[1] for write
    int a, b, c, sum;

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    printf("Enter three integers (a, b, c) for expression (a+b)*c: ");
    scanf("%d %d %d", &a, &b, &c);

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child Process: evaluates (a+b)
        close(fd[0]); // Close unused read end
        sum = a + b;
        printf("Child: Computed sum (a+b) = %d. Sending to parent...\n", sum);
        write(fd[1], &sum, sizeof(sum));
        close(fd[1]);
        exit(0);
    } else {
        // Parent Process: evaluates result * c
        close(fd[1]); // Close unused write end
        wait(NULL);
        read(fd[0], &sum, sizeof(sum));
        int result = sum * c;
        printf("Parent: Received sum %d. Final Result ((a+b)*c) = %d\n", sum, result);
        close(fd[0]);
    }

    return 0;
}
