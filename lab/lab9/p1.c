// Reader Writer Problem

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<fcntl.h>
#include<string.h>

sem_t rw_mutex;
sem_t mutex;
int read_count;

#define READER 10
#define WRITER 1
int count;
void *reader(void*);
void *writer(void*);

char filename[10] = "file";
int fd;

int main(int argc, char const *argv[])
{
    count = 0;
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);
    read_count = 0;
    pthread_t thread[2];
    int idr[READER];
    int idw[WRITER];
    int i;
    for(i = 0; i < WRITER; i++)
    {
        idw[i] = i;
        pthread_create(&thread[1], NULL, writer, idw+i);
    }
    for(i = 0; i < READER; i++)
    {
        idr[i] = i;
        pthread_create(&thread[0], NULL, reader, idr+i);
    }
    for(i = 0; i < WRITER; i++)
    {
        pthread_join(thread[1], NULL);
    }
    for(i = 0; i < READER; i++)
    {
        pthread_join(thread[0], NULL);
    }
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);
    return 0;
}

void *writer(void *param) {
    int id = *(int *)param;
    id++;
    char message[100];
    do{
        sem_wait(&rw_mutex);
        fd = open(filename, O_WRONLY | O_TRUNC);
        printf("Writer %d is writing\n", id);
        sleep(1);
        // Writing is performed
        int len = sprintf(message, "hello %d\n", count++);
        write(fd, message, len);
        close(fd);
        sem_post(&rw_mutex);
    }while(1);
    
}


void *reader(void *param) {
    int id = *(int *)param;
    id++;
    char message[100];
    do {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1){
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);
        // Reading
        fd = open(filename, O_RDONLY);
        read(fd, message, 6);
        printf("Reader %d read %s\n", id, message);
        sleep(1);
        close(fd);
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0){
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);
    }while(1);
}