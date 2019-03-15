// Implement Banker's Algorithm

#include<stdio.h>

#define NUM_RESOURCES 3
#define NUM_PROCESS 5

int check_availability(int *available, int *need);
void use_resource(int *available, int *allocated);
int all_completed(int *completed);

int main(int argc, char const *argv[])
{
    printf("BANKER'S ALGORITHM\n");
    // Initializing resources    
    int available[NUM_RESOURCES] = {0, 0, 2};
    // TODO: Add user input to all the matrices
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
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {3, 3, 2}
    };
    int need[NUM_PROCESS][NUM_RESOURCES] = 
    {
        {7, 4, 3},
        {1, 2, 2},
        {6, 0, 0},
        {0, 1, 1},
        {1, 0, 1}
    };
    int completed[NUM_PROCESS] = {0, 0, 0, 0};
    // TODO: Extract the deadlock check to a function
    int deadlock = 0, i;
    while (!all_completed(completed) && !deadlock) {
        // It will be zero if atleast one process gets allocated
        deadlock = 1;
        for (i = 0; i<NUM_PROCESS; i++){
            if ( !completed[i] && check_availability(available, need[i]) ){
                deadlock = 0;
                use_resource(available, allocation[i]);
                completed[i] = 1;
            }
        }
    }
    if (deadlock) {
        printf("Deadlock Occured\n");
    }
    else {
        printf("Completed allocation to all processes.\n");
        printf("Final resources availabilty\n");
        for (i = 0; i<NUM_RESOURCES; i++) {
            printf("%d\t", available[i]);
        }
        printf("\n");
    }

    return 0;
}

int check_availability(int *availble, int *need) {
    int i;
    for ( i=0; i<NUM_RESOURCES; i++) {
        if (availble[i] < need[i]){
            return 0;
        }
    }
    return 1;
}
void use_resource( int *available, int *allocated) {
    int i;
    for( i = 0; i < NUM_RESOURCES; i++)
    {
        available[i] += allocated[i];
    }
}

int all_completed(int *completed){
    for (int i = 0; i < NUM_PROCESS; i++) {
        if (completed[i] == 0){
            return 0;
        }
    }
    return 1;
}