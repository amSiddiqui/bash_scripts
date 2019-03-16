// Bound buffer problem using semaphores

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define NUM_PRODUCER 10
#define NUM_CONSUMER 10
#define BUFFER_SIZE 4
typedef int buffer_t;

buffer_t buffer[BUFFER_SIZE]; // Implemented as stack
int pointer;

sem_t mutex;
sem_t empty;
sem_t full;

void *produce(void *param);
void *consume(void *param);
void push(int val);
int pop();

int main(int argc, char const *argv[])
{
    sem_init(&mutex, 1, 1);
    sem_init(&empty, 1, BUFFER_SIZE-1);
    sem_init(&full, 1, 0);
    pointer = 0;
    int p_id[NUM_PRODUCER];
    int c_id[NUM_CONSUMER];
    
    pthread_t p_thread[NUM_PRODUCER];
    pthread_t c_thread[NUM_CONSUMER];
    int i;
    for(i = 0; i < NUM_PRODUCER; i++)
    {
        p_id[i] = i;
        pthread_create(p_thread + i, NULL, produce, p_id + i);
    }

    for(i = 0; i < NUM_CONSUMER; i++)
    {
        c_id[i] = i;
        pthread_create(c_thread + i, NULL, consume, c_id + i);
    }
    
    for(i = 0; i < NUM_PRODUCER; i++)
    {
        pthread_join(p_thread[i], NULL);
    }

    for(i = 0; i < NUM_CONSUMER; i++)
    {
        pthread_join(c_thread[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

void push(int val) {
    if (pointer >= BUFFER_SIZE -1){
        printf("Buffer Overflow Error\n");
        exit(1);
    }
    buffer[++pointer] = val;
}

int pop() {
    if (pointer == 0) {
        printf("Buffer underflow Error\n");
        exit(1);
    }
    return buffer[pointer--];
}

void *produce(void *param) {
    int id = *(int*) param;
    id++;
    do{
        int next_value = rand() % 100;
        sleep(1);
        sem_wait(&empty);
        sem_wait(&mutex);
        push(next_value);
        printf("Producer %d produced %d\n", id, next_value);
        sem_post(&mutex);
        sem_post(&full);
    }while(1);
}

void *consume(void *param) {
    int id = *(int *) param;
    id++;
    do{
        sem_wait(&full);
        sem_wait(&mutex);
        sleep(1);
        printf("Consumer %d consumed %d\n", id, pop());
        sem_post(&mutex);
        sem_post(&empty);
    }while(1);
}