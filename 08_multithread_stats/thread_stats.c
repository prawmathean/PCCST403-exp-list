#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Global variables for threads to update
int *data;
int n;
double mean, median, std_dev;

void *calc_mean(void *arg) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += data[i];
    mean = sum / n;
    pthread_exit(0);
}

void *calc_median(void *arg) {
    // Sort the array first
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                int temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
    
    if (n % 2 == 0)
        median = (double)(data[n / 2 - 1] + data[n / 2]) / 2.0;
    else
        median = (double)data[n / 2];
        
    pthread_exit(0);
}

void *calc_std_dev(void *arg) {
    double sum_sq_diff = 0;
    for (int i = 0; i < n; i++) {
        sum_sq_diff += pow(data[i] - mean, 2);
    }
    std_dev = sqrt(sum_sq_diff / n);
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <num1> <num2> ... <numN>\n", argv[0]);
        return 1;
    }

    n = argc - 1;
    data = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        data[i] = atoi(argv[i + 1]);
    }

    pthread_t t1, t2, t3;

    // Create threads for mean and median
    pthread_create(&t1, NULL, calc_mean, NULL);
    pthread_create(&t2, NULL, calc_median, NULL);

    // Wait for mean and median threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Now that mean is calculated, we can calculate std dev
    pthread_create(&t3, NULL, calc_std_dev, NULL);
    pthread_join(t3, NULL);

    printf("--- Statistics Result ---\n");
    printf("Mean: %.2f\n", mean);
    printf("Median: %.2f\n", median);
    printf("Standard Deviation: %.2f\n", std_dev);

    free(data);
    return 0;
}
