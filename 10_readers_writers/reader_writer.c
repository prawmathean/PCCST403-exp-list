#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

/* Readers-Writers with Writer Priority */

sem_t resource, rcheck, wcheck, readTry, resourceAccess;
int read_count = 0, write_count = 0;
sem_t r_mutex, w_mutex;

void* reader(void* arg) {
    int id = *(int*)arg;
    
    sem_wait(&readTry);         // Reader tries to enter
    sem_wait(&r_mutex);         // Lock to update read_count
    read_count++;
    if (read_count == 1) sem_wait(&resourceAccess); // First reader locks resource
    sem_post(&r_mutex);
    sem_post(&readTry);         // Reader is in
    
    printf("Reader %d is reading...\n", id);
    sleep(1);
    
    sem_wait(&r_mutex);
    read_count--;
    if (read_count == 0) sem_post(&resourceAccess); // Last reader releases resource
    sem_post(&r_mutex);
    
    printf("Reader %d left.\n", id);
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    
    sem_wait(&w_mutex);
    write_count++;
    if (write_count == 1) sem_wait(&readTry); // First writer blocks new readers
    sem_post(&w_mutex);
    
    sem_wait(&resourceAccess);  // Writer locks resource for writing
    printf("Writer %d is WRITING!!!\n", id);
    sleep(2);
    sem_post(&resourceAccess);
    
    sem_wait(&w_mutex);
    write_count--;
    if (write_count == 0) sem_post(&readTry); // Last writer allows readers again
    sem_post(&w_mutex);
    
    printf("Writer %d left.\n", id);
    return NULL;
}

int main() {
    pthread_t r[3], w[2];
    int ids[] = {1, 2, 3};
    
    sem_init(&r_mutex, 0, 1);
    sem_init(&w_mutex, 0, 1);
    sem_init(&readTry, 0, 1);
    sem_init(&resourceAccess, 0, 1);

    pthread_create(&w[0], NULL, writer, &ids[0]);
    pthread_create(&r[0], NULL, reader, &ids[0]);
    pthread_create(&r[1], NULL, reader, &ids[1]);
    pthread_create(&w[1], NULL, writer, &ids[1]);
    pthread_create(&r[2], NULL, reader, &ids[2]);

    for(int i=0; i<3; i++) pthread_join(r[i], NULL);
    for(int i=0; i<2; i++) pthread_join(w[i], NULL);

    return 0;
}
