#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define size 2

sem_t empty, full;
int count=0;
int buffer[size];
pthread_mutex_t mutex;

int loop=20;

void* producer(void* argv){
    int x, t;
    for(int i=0; i<loop; ++i){
        x = rand() % 2 + 1;
        sem_wait(&empty);
        t = rand() % 2 + 1;
        sleep(t);
        pthread_mutex_lock(&mutex);
        buffer[count] = x;
        count = count + 1;
        printf("Item produced, there are now %d item(s) in the table.\n", count);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return 0;
}

void* consumer(void* argv){
    for(int i=0; i<loop; ++i){
        sem_wait(&full);
        int t = rand() % 2 + 1;
        sleep(t);
        pthread_mutex_lock(&mutex);
        int x = buffer[count];
        count = count - 1;
        printf("Item consumed, %d remaining.\n", count);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    return 0;
}

int main() {
	
	pthread_t prod, cons;
	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, size);
	sem_init(&full, 0, 0);
	
	pthread_create(&prod, NULL, (void *)producer, NULL);
	pthread_create(&cons, NULL, (void *)consumer, NULL);
	pthread_join(prod, NULL);
	pthread_join(cons, NULL);
    
	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);

    return 0;
}
