// Implement Banker's Algorithm

#include<stdio.h>

#define NUM_RESOURCES 3
#define NUM_PROCESS 5

int main(int argc, char const *argv[])
{
    printf("BANKER'S ALGORITHM\n");
    // Initializing resources    
    int available[NUM_RESOURCES] = {3, 3, 2};
    int max[NUM_PROCESS][NUM_RESOURCES] = 
    {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int allocation[NUM_PROCESS][NUM_RESOURCES] = 
    {
        {}
    }
    ;
    int need[NUM_PROCESS][NUM_RESOURCES];

    return 0;
}
