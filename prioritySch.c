#include <stdio.h>
#include <stdlib.h>

/*
Arrival Time    - Time when Process is inserted
Completion Time - Process eecuted TimeStamp
Burst Time      - Execution Time of Process
Turn Around Time- Completion time - Arrival Time
Wait Time       - Turn Around Time - Burst Time
*/

struct process
{
    int process_id;
    int priority;
    int burst_time; // Time to complete
};

swapProcess(struct process *proc1, struct process *proc2)
{
    struct process temp = *proc1;
    *proc1 = *proc2;
    *proc2 = temp;
}

sortPriority(struct process proc[], int n, int (*compare)(struct process a, struct process b))
{
    int max_index, i;

    printf("Length of Process = %d \n", n);
    for(i=0;i<n-1;i++)
    {
        max_index = i;
        for(int j = i+1; j<n; j++)
        {
            if((*compare)(proc[j] , proc[max_index]))
                max_index = j;
        }
        swapProcess(&proc[max_index], &proc[i]);
    }
}

int comparison(struct process a, struct process b) 
{ 
    return (a.priority > b.priority); 
} 

void schedule(struct process proc[], int n)
{
    sortPriority(proc, n, comparison); 

    printf("Order in which processes gets executed \n");
    for (int  i = 0 ; i <  n; i++) 
        printf("%d ", proc[i].process_id); 
}

void main()
{
    // Create some Processes
    struct process proc[] = {{1,0,10},{2,3,15},{3,2,5}};
    int num_process = sizeof(proc)/sizeof(proc[0]);

    schedule(proc, num_process);
}