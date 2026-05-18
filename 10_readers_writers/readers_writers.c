#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

sem_t resource_access; // Controls access to the resource
sem_t read_count_access; // Controls access to read_count
sem_t write_count_access; // Controls access to write_count
sem_t service_queue; // Ensures writers can block new readers

int read_count = 0;
int write_count = 0;

void* reader(void* arg) {
    int id = *(int*)arg;

    // Entry Section
    sem_wait(&service_queue); // Wait if a writer is in queue
    sem_wait(&read_count_access);
    read_count++;
    if (read_count == 1) {
        sem_wait(&resource_access); // First reader locks resource
    }
    sem_post(&read_count_access);
    sem_post(&service_queue);

    // Reading
    printf("Reader %d is reading...\n", id);
    sleep(rand() % 2 + 1);

    // Exit Section
    sem_wait(&read_count_access);
    read_count--;
    if (read_count == 0) {
        sem_post(&resource_access); // Last reader unlocks resource
    }
    sem_post(&read_count_access);

    printf("Reader %d finished reading.\n", id);
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;

    // Entry Section
    sem_wait(&write_count_access);
    write_count++;
    if (write_count == 1) {
        sem_wait(&service_queue); // First writer blocks the service queue
    }
    sem_post(&write_count_access);

    sem_wait(&resource_access); // Lock the resource for writing
    
    // Writing
    printf("Writer %d is writing!!!\n", id);
    sleep(rand() % 3 + 1);
    
    sem_post(&resource_access); // Unlock

    // Exit Section
    sem_wait(&write_count_access);
    write_count--;
    if (write_count == 0) {
        sem_post(&service_queue); // Last writer opens the service queue
    }
    sem_post(&write_count_access);

    printf("Writer %d finished writing.\n", id);
    return NULL;
}

int main() {
    int r_ids[] = {1, 2, 3, 4, 5};
    int w_ids[] = {1, 2};
    pthread_t r_threads[5], w_threads[2];

    sem_init(&resource_access, 0, 1);
    sem_init(&read_count_access, 0, 1);
    sem_init(&write_count_access, 0, 1);
    sem_init(&service_queue, 0, 1);

    for (int i = 0; i < 5; i++) pthread_create(&r_threads[i], NULL, reader, &r_ids[i]);
    for (int i = 0; i < 2; i++) pthread_create(&w_threads[i], NULL, writer, &w_ids[i]);

    for (int i = 0; i < 5; i++) pthread_join(r_threads[i], NULL);
    for (int i = 0; i < 2; i++) pthread_join(w_threads[i], NULL);

    sem_destroy(&resource_access);
    sem_destroy(&read_count_access);
    sem_destroy(&write_count_access);
    sem_destroy(&service_queue);

    return 0;
}
