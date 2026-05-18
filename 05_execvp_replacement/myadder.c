#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <num1> <num2>\n", argv[0]);
        return 1;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    printf("\n[myadder] Received: %d and %d\n", a, b);
    printf("[myadder] Sum: %d\n", a + b);

    return 0;
}
