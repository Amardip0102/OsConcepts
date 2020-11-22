// C program to demonstrate working of Semaphores 
#include <stdio.h> 
#include <pthread.h>
#include <unistd.h> 

typedef void* sem_t;
sem_t mutex; 

void mysem_init(void *mutex, int shared, int value)
{
    *((int *)mutex) = value;
}

void mysem_wait(void *mutex)
{
    while(!*((int *)mutex));
    *((int *)mutex) = 0;
}

void mysem_post(void *mutex)
{
    *((int *)mutex) = 1;
}

void mysem_destroy(void *mutex)
{
    mutex = NULL;
}

void* thread(void* arg) 
{ 
	//wait 
	mysem_wait(&mutex); 
	printf("\nEntered..\n"); 

    //sem_wait(&mutex); this will cause Deadlock - 
    // since it will wait here for some one else to post the semaphore. This is the thread which can post semaphore.
	//critical section 
	sleep(4); 
	
	//signal 
	printf("\nJust Exiting...\n"); 
	mysem_post(&mutex); 
} 


int main() 
{ 

    /*Semaphore Usecase*/
	mysem_init(&mutex, 0, 1); 
	pthread_t t1,t2; 
	pthread_create(&t1,NULL,thread,NULL); 
	sleep(2); 
	pthread_create(&t2,NULL,thread,NULL); 
	pthread_join(t1,NULL); 
	pthread_join(t2,NULL); 
	mysem_destroy(&mutex); 
	return 0; 
} 
