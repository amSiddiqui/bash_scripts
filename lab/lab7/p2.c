#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;

void *manipal(void *param);
void *university(void *param);
void *jaipur(void *param);

int main(int argc, char const *argv[])
{
    if( pthread_mutex_init(&lock, NULL) != 0 ){
        fprintf(stderr, "Mutex intit failed\n");
        return 1;
    }
    pthread_t thread[3];
    pthread_create(&thread[0], NULL, manipal, NULL); 
    pthread_create(&thread[1], NULL, university, NULL); 
    pthread_create(&thread[2], NULL, jaipur, NULL);

    pthread_join(thread[0], NULL); 
    pthread_join(thread[1], NULL); 
    pthread_join(thread[2], NULL);
    pthread_mutex_destroy(&lock); 
    return 0;
}

void *manipal(void *param){
    pthread_mutex_lock(&lock);
    printf("Manipal ");
    pthread_mutex_unlock(&lock);
    pthread_exit(0);
}

void *university(void *param){
    pthread_mutex_lock(&lock);
    printf("University ");
    pthread_mutex_unlock(&lock);
    pthread_exit(0);
}

void *jaipur(void *param){
    pthread_mutex_lock(&lock);
    printf("Jaipur \n");
    pthread_mutex_unlock(&lock);
    pthread_exit(0);
}