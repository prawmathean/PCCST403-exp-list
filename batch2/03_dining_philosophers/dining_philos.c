#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define N 5 // Number of philosophers

sem_t forks[N];

void* philosopher(void* arg) {
    int id = *(int*)arg;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(rand() % 2 + 1);

        // To avoid deadlock: 
        // Even-numbered philosophers pick left then right
        // Odd-numbered philosophers pick right then left
        if (id % 2 == 0) {
            sem_wait(&forks[id]); // Pick left
            sem_wait(&forks[(id + 1) % N]); // Pick right
        } else {
            sem_wait(&forks[(id + 1) % N]); // Pick right
            sem_wait(&forks[id]); // Pick left
        }

        printf("Philosopher %d is EATING 🍜\n", id);
        sleep(rand() % 3 + 1);

        // Put down forks
        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % N]);

        printf("Philosopher %d finished eating.\n", id);
    }
    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];

    // Initialize semaphores (forks)
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
        ids[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    // Join threads (in this case, it runs forever)
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    // Cleanup
    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
