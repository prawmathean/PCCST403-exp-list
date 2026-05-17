#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

/* Multithreaded Stats: Mean, Median, Standard Deviation */

int *arr, n;
double mean, median, std_dev;

void* calc_mean(void* arg) {
    double sum = 0;
    for(int i=0; i<n; i++) sum += arr[i];
    mean = sum / n;
    pthread_exit(0);
}

void* calc_median(void* arg) {
    // Basic bubble sort for median
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n-i-1; j++)
            if(arr[j] > arr[j+1]) {
                int temp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = temp;
            }
    if(n%2 == 0) median = (arr[n/2] + arr[n/2-1]) / 2.0;
    else median = arr[n/2];
    pthread_exit(0);
}

void* calc_std_dev(void* arg) {
    // Wait for mean to be calculated? No, we can just calc it here too to keep it independent
    double sum = 0, m = 0;
    for(int i=0; i<n; i++) m += arr[i];
    m /= n;
    for(int i=0; i<n; i++) sum += pow(arr[i] - m, 2);
    std_dev = sqrt(sum / n);
    pthread_exit(0);
}

int main() {
    printf("Enter number of elements: ");
    scanf("%d", &n);
    arr = (int*)malloc(n * sizeof(int));
    printf("Enter %d numbers: ", n);
    for(int i=0; i<n; i++) scanf("%d", &arr[i]);

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, calc_mean, NULL);
    pthread_create(&t2, NULL, calc_median, NULL);
    pthread_create(&t3, NULL, calc_std_dev, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("\nResults:\nMean: %.2f\nMedian: %.2f\nStd Deviation: %.2f\n", mean, median, std_dev);
    
    free(arr);
    return 0;
}
