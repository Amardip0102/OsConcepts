#include <stdio.h>

void findWaitingTime(int processes[], int n, 
			int bt[], int wt[], int quantum) 
{ 
	// Make a copy of burst times bt[] to store remaining 
	// burst times. 
	int rem_bt[n]; 
	for (int i = 0 ; i < n ; i++) 
		rem_bt[i] = bt[i]; 

	int t = 0; // Current time 

	// Keep traversing processes in round robin manner 
	// until all of them are not done. 
	while (1) 
	{ 
		int done = 1; 

		// Traverse all processes one by one repeatedly 
		for (int i = 0 ; i < n; i++) 
		{ 
			// If burst time of a process is greater than 0 
			// then only need to process further 
			if (rem_bt[i] > 0) 
			{ 
				done = 0; // There is a pending process 

				if (rem_bt[i] > quantum) 
				{ 
					// Increase the value of t i.e. shows 
					// how much time a process has been processed 
					t += quantum; 

					// Decrease the burst_time of current process 
					// by quantum 
					rem_bt[i] -= quantum; 
				} 

				// If burst time is smaller than or equal to 
				// quantum. Last cycle for this process 
				else
				{ 
					// Increase the value of t i.e. shows 
					// how much time a process has been processed 
					t = t + rem_bt[i]; 

					// Waiting time is current time minus time 
					// used by this process 
					wt[i] = t - bt[i]; 

					// As the process gets fully executed 
					// make its remaining burst time = 0 
					rem_bt[i] = 0; 
				} 
			} 
		} 

		// If all processes are done 
		if (done == 1) 
		break; 
	} 
} 

findWaitTime(int proc[], int bt[],int wt[], int quantum, int n)
{
    int remTime[n];
    for(int i=0; i<n;i++)
        remTime[i] = bt[i]; //Copy Burst Time to check Remaining Time later

    int t = 0; //current Time Stamp;
    while (1)
    {
        /* code */
        int done = 1; // Complete Flag
        for(int i=0; i<n; i++)
        {
            // Schedule one by one
            if(remTime[i] > 0)
            {
                done = 0;   // Since still some processes are remaining set done as false
                t += quantum;
                remTime[i]-=quantum;
            }
            else
            {
                /* code */
                t = t + remTime[i]; //keep adding total time
                wt[i] = t - bt[i]; // total time - burst time
                remTime[i] = 0; // remaining time is elapsed
            }
            
        }

        if(done == 1)
            break;
    }

    
}

findTurnAroundTime(int wt[],int n,int tat[],int bt[])
{
    for(int i=0;i<n;i++)
    {
        tat[i] = wt[i] + bt[i];
    }
}

findAvgTime(int processes[],int burst_time[], int n, int quantum)
{
    // Wait Time, TAT, TAT = Wait + Burst
    int wt[n], tat[n];
    int avg_wt = 0, total_wt=0, avg_tat=0, total_tat=0;

    //findWaitTime(processes,burst_time,wt,quantum,n);
    findWaitingTime(processes, n, burst_time, wt,quantum);
    findTurnAroundTime(wt,n,tat,burst_time);

    	// Display processes along with all details 
	printf("Processes Burst time Waiting time Turn around time\n"); 

	// Calculate total waiting time and total turn 
	// around time 
	for (int i=0; i<n; i++) 
	{ 
		total_wt = total_wt + wt[i]; 
		total_tat = total_tat + tat[i];
        printf(" %d \t\t %d \t\t %d \t %d \t\t \n",i+1, burst_time[i], wt[i], tat[i]);
	} 

    for(int i=0;i<n;i++)
    {
        total_tat +=tat[i];
        total_wt +=wt[i];
    }

    printf("Average TAT = %f \n", (float)total_tat/(float)n);
    printf("Average WT = %f \n", (float)total_wt/(float)n);
}

void main()
{
	int processes[] = { 1, 2, 3}; 
	int n = sizeof processes / sizeof processes[0]; 

	// Burst time of all processes 
	int burst_time[] = {10, 5, 8}; 
    int quantum = 2; // Each Loop Time;

    findAvgTime(processes, burst_time, n, quantum);
}