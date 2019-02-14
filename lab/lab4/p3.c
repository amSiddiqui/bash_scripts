// This program creates a zombie process 

// To see the zombie process created 
// Press Ctrl+Z to stop the parent prcess. Or open a new Terminal
// type: ps -el | grep a.out
// The output has both parent(a.out) and child(a.out<defunct>).
// Child has a flag fo Z suggesting zombie. 

#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{  
    pid_t id = fork(); 
    // Child process exits 
    if (id == 0) 
        exit(0); 

    // Parent process sleeps for 50 seconds
    else        
        sleep(50); 
  
    return 0; 
} 