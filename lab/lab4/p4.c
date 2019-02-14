#include<stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 

// To see the orphan process created 
// type: ps -el | grep a.out
// Process a.out with a parent id as 1 (init id) is an orphan process.

int main() 
{        
    pid_t id = fork(); 
    
    if (id == 0) {
        // Sleep the child process for 50
        sleep(20); 
        // This line will be printed out after 20 seconds
        printf("in child process\n"); 
    }
    else
    { 
        // Parent is terminated
        printf("in parent process\n"); 
    } 
    return 0; 
} 