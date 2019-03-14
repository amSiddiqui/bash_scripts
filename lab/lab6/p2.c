// Sessional Program 2
// Write a multithreaded program in which the child thread will display prime numbers less
// than or equal to the number entered by the user through command line.


// Note to compile this program use.
// gcc p2.c -lpthread 
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/types.h>

int prime_check(int);
void *run(void*);

int main(int argc, char const *argv[])
{
    // Input file name from command line
    if ( argc < 2) {
        fprintf(stderr, "Please enter a number.\n");
        return 1;
    }
    else if (argc > 2) {
        fprintf(stderr, "Please enter only one number.\n");
        return 1;
    }
    if (atoi(argv[1]) < 0) {
        fprintf(stderr,"%d must be >= 0 \n", atoi(argv[1]));
        return 1;
    }
    // Creating thread
    pthread_t tid;
    pthread_attr_t attr;

    // get the default attributes
    pthread_attr_init(&attr);
    // create the thread 
    pthread_create(&tid, &attr, run, (void *)argv[1]);
    // wait for the thread to exit
    pthread_join(tid,NULL);
    printf("Thread completed Parent exiting.\n");
}

void *run(void* param){
    // Runner function that prints if number is prime.
    int num = atoi(param);
    int i;
    printf("Prime numbers less than %d are: ", num);
    for (i = 2; i< num; i++){
        if(prime_check(i)){
            printf("%d, ",i);
        }
    }
    printf("\n");
    pthread_exit(0);
}

int prime_check(int n){
    // Corner cases 
    if (n <= 1)  return 0; 
    if (n <= 3)  return 1; 
  
    // This is checked so that we can skip  
    // middle five numbers in below loop 
    if (n%2 == 0 || n%3 == 0) return 0; 
  
    for (int i=5; i*i<=n; i=i+6) 
        if (n%i == 0 || n%(i+2) == 0) 
           return 0; 
  
    return 1; 
}