//  C program for implementation of SJF  
//  scheduling  
#include<stdio.h>  

// Sorts arr and its index
void bubble_sort(int arr[], int index[], int n){
    int i, j, temp;
    for (i = 0; i<n-1; i++){
        for (j = 0; j<n-i-1; j++){
            if(arr[j]>arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                temp = index[j];
                index[j] = index[j+1];
                index[j+1] = temp;
            }
        }
    }
}


//  Function to find the waiting time for all   
//  processes  
void findWaitingTime(int processes[], int n, int bt[], int wt[])  
{  
    //  waiting time for first process is 0  
    wt[0] = 0;  
    
    //  calculating waiting time  
    for (int  i = 1; i < n ; i++ )  
        wt[i] =  bt[i-1] + wt[i-1];  
}  
    
//  Function to calculate turn around time  
void findTurnAroundTime( int processes[], int n, int bt[], int wt[], int tat[])  
{  
    //  calculating turnaround time by adding  
    //  bt[i] + wt[i]  
    for (int  i = 0; i < n ; i++)  
        tat[i] = bt[i] + wt[i];  
}  
    
// Function to calculate average time  
void findavgTime( int processes[], int n, int bt[])  
{  
    int wt[n], tat[n], total_wt = 0, total_tat = 0;  
    
    bubble_sort(bt, processes, n);

    // Function to find waiting time of all processes  
    findWaitingTime(processes, n, bt, wt);  
    
    // Function to find turn around time for all processes  
    findTurnAroundTime(processes, n, bt, wt, tat);  
    
    // Display processes along with all details  
    printf("Processes\tBurst time\tWaiting time\tTurn around time\n");  
    
    //  Calculate total waiting time and total turn   
    //  around time  
    for (int  i=0; i<n; i++)  
    {  
        total_wt = total_wt + wt[i];  
        total_tat = total_tat + tat[i];  
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i] , bt[i], wt[i], tat[i]);  
    }  
    int s=(float)total_wt / (float)n; 
    int t=(float)total_tat / (float)n; 
    printf("Average waiting time = %d\n",s);  
    printf("Average turn around time = %d\n",t);  
}  

int main()  
{  
    // process id's  
    int processes[] = {1, 2, 3, 4, 5};  
    int n = sizeof processes / sizeof processes[0];  
    
    // Burst time of all processes  
    int  burst_time[] = {10, 5, 8, 9, 11};  
    
    findavgTime(processes, n,  burst_time);  
    return 0;  
}

