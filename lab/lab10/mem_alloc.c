// Memory allocation 
// First fit, best fit, worst fit algo.
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MEM_LOCS 20
#define PROCESS 5
int mem_blocks[MEM_LOCS];

void seed_mem (int *);
void print_arr(int *, int);
void arr_cpy(int *, int *, int);
void best_fit(int *mem, int *proc, int *p_alloc);
void first_fit(int *mem, int *proc, int *p_alloc);
void worst_fit(int *mem, int *proc, int *p_alloc);
void input_proc (int *proc);

int main(int argc, char const *argv[])
{
    seed_mem(mem_blocks);
    int process[PROCESS];
    int p_alloc[PROCESS];
    input_proc(process);
    puts ("Memory Sizes:");
    print_arr(mem_blocks, MEM_LOCS);
    puts("BEST FIT");
    best_fit(mem_blocks, process, p_alloc);
    puts("Process memory allocations using best fit: ");
    print_arr(p_alloc, PROCESS);
    puts("WORST FIT");
    worst_fit (mem_blocks, process, p_alloc);
    puts("Process memory allocations using worst fit: ");
    print_arr(p_alloc, PROCESS);
    puts("FIRST FIT");
    first_fit (mem_blocks, process, p_alloc);
    puts("Process memory allocations using first fit: ");
    print_arr(p_alloc, PROCESS);
    return 0;
}

void seed_mem (int mem_loc[]) {
    srand(time(0));
    for(size_t i = 0; i < MEM_LOCS; i++)
    {
        mem_blocks[i] = rand()%180 + 20;
    }
}

void print_arr(int arr[], int len) {
    for(size_t i = 0; i < len-1; i++)
    {
        printf("%d, ", arr[i]);
    }
    printf("%d\n", arr[len-1]);
}

void arr_cpy (int arr[], int narr[], int len) {
    for(size_t i = 0; i < len; i++)
    {
        narr[i] = arr[i];
    }
    
}
void input_proc(int proc[]) {
    puts("Enter process memory Sizes");
    for(int i = 0; i < PROCESS; i++)
    {
        printf("Process %d: ", i+1);
        scanf("%d", &proc[i]);
    }
}

void best_fit(int mem[], int proc[], int p_alloc[]) {
    int cur_mem[MEM_LOCS];
    arr_cpy(mem, cur_mem, MEM_LOCS);
    // Find smallest mem block just greater than ith process
    int best;
    for(int i = 0; i < PROCESS; i++)
    {
        // Find best fit process loc
        best = 0;
        for(size_t j = 1; j < MEM_LOCS; j++)
        {
            if (cur_mem[j] > cur_mem[best] && cur_mem[j] >= proc[i])
                best = j;
        }
        p_alloc[i] = best;
        cur_mem[best] = cur_mem[best] - proc[i]; 
        // printf("Process %d allocated in %d location\n", i+1, best);
        // puts("New Mem blocks");
        // print_arr(cur_mem, MEM_LOCS);
    }
    
}
void worst_fit(int mem[], int proc[], int p_alloc[]) {
    int cur_mem[MEM_LOCS];
    arr_cpy(mem, cur_mem, MEM_LOCS);
    // Find smallest mem block just less than ith process
    int worst;
    for(int i = 0; i < PROCESS; i++)
    {
        // Find best fit process loc
        worst = 0;
        for(size_t j = 1; j < MEM_LOCS; j++)
        {
            if (cur_mem[j] > cur_mem[worst] && cur_mem[j] >= proc[i])
                worst = j;
        }
        p_alloc[i] = worst;
        cur_mem[worst] = cur_mem[worst] - proc[i]; 
        // printf("Process %d allocated in %d location\n", i+1, worst);
        // puts("New Mem blocks");
        // print_arr(cur_mem, MEM_LOCS);
    }
}

void first_fit(int mem[], int proc[], int p_alloc[]) {
    int cur_mem[MEM_LOCS];
    arr_cpy(mem, cur_mem, MEM_LOCS);
    // Find smallest mem block just less than ith process
    int first;
    for(int i = 0; i < PROCESS; i++)
    {
        // Find best fit process loc
        first = 0;
        for(size_t j = 0; j < MEM_LOCS; j++)
        {
            if (cur_mem[j] >= proc[i]) {
                first = j;
                break;
            }

        }
        p_alloc[i] = first;
        cur_mem[first] = cur_mem[first] - proc[i]; 
        // printf("Process %d allocated in %d location\n", i+1, first);
        // puts("New Mem blocks");
        // print_arr(cur_mem, MEM_LOCS);
    }
}
