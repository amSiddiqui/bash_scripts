// Write a program that creates a child process using fork()
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(){
    pid_t id, cpid;
    id = fork();
    if(id == 0){
        // This part will be executed in child process
        printf("This is the child process with id: %d\n", getpid());
        printf("Parent process id : %d\n", getppid());
    }else{
        // This part will be executed in parent process
        // Wait for child to be finished
        cpid = wait(NULL);
        printf("This is the parent process with id: %d\n", getpid());
        printf("The child process that it was waiting for is: %d\n", cpid);
    }
    return 0;
}