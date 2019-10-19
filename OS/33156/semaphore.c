#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BUF_SIZE 10
#define NP 10
#define NC 10
#define NITEMS 4

typedef struct
{
	int buff[BUF_SIZE];		//buffer resource/variable
	int in;						//first empty slot
	int out;					//first full slot
	sem_t full;					//no of full slots
	sem_t empty;				//no of empty slots
	pthread_mutex_t mutex;		//mutex for shared resource
	
}sbuf_t;

sbuf_t shared;

void* producer(void* arg)
{
	/*i : iterator for the for loop
	  item : item that will be produced by the producer
	  index : index of the buffer */
	int i,item,index;	
	
	//type cast the void* arg to use for production
	index = (int)arg;
	
	//for loop for producing items
	for(i=0;i<NITEMS;i++)
	{
		item = rand() % 10; //produce item of value "i"
		
		//prepare to write to the buffer
		
		/*if buffer is full, i.e.,empty=0, the calling thread from 
		sem_wait() will never return, until it either locks the semaphore 
		or is interrupted by a system call*/
		sem_wait(&shared.empty);
		
		//if another thread is using the shared rsrc, block mutex
		pthread_mutex_lock(&shared.mutex);
		
		//item written to buffer
		shared.buff[shared.in] = item;	
		
		printf("\nProducer [%d] produced item (%d) at buffer location [%d]!\n",index,item,shared.in);
		
		//update the last empty slot in the buffer
		shared.in = (shared.in + 1) % BUF_SIZE;
		
		
		//flush the buffer
		fflush(stdout);
		
		//Unblock the mutex
		pthread_mutex_unlock(&shared.mutex);
		
		//Unblock the full semaphore
		sem_post(&shared.full);
	
		sleep(rand() % 10);
	}
	
	return NULL;
}

void* consumer(void* arg)
{
	/*i : iterator for the for loop
	  item : var where the buffer value will be read
	  index : index of the buffer*/
	int i, item, index;
	
	//copy arg value into index to perform comsumption
	index = (int)arg;
	
	for(i=NITEMS;i>0;i--)
	{
		//if buffer is empty, sem_wait() will block the semaphore
		sem_wait(&shared.full);
		
		//else block the mutex for consumption
		pthread_mutex_lock(&shared.mutex);
		
		
		
		//read value from buffer at the "out" index and write to item
		item = shared.buff[shared.out];
		
		printf("\nConsumer [%d] consumed item (%d) at buffer location [%d]!\n",index,item,shared.out);
		
		//increment the out value of buffer
		shared.out = (shared.out + 1) % BUF_SIZE;
		
		//flush the buffer
		fflush(stdout);
		
		//unblock the mutex after consumption
		pthread_mutex_unlock(&shared.mutex);
		
		//release the resrc
		sem_post(&shared.empty);
		
		sleep(rand() % 10);
	}
	
	return NULL;
}

int main()
{
	/*Pid : process ID of producer process
	  Cid : process ID of consumer process*/
	pthread_t Pid, Cid;
	
	//init full value to 0
	sem_init(&shared.full, 0 ,0);
	//init empty value to max buffer size
	sem_init(&shared.empty, 0, BUF_SIZE);
	
	//initialise mutex value to NULL
	pthread_mutex_init(&shared.mutex, NULL);
	
	int i;
	shared.in = 0;
	shared.out = 0;
	
	//Producer threads creattion
	for(i=0;i<NP;i++)
	{
		//printf("\n----Producer Thread %d started----",i);
		pthread_create(&Pid, NULL, producer, (void*)i);
		
	}	
	
	//Consumer threads creation
	for(i=0;i<NC;i++)
	{
		//printf("\n----Consumer Thread %d started----",i);
		pthread_create(&Cid, NULL, consumer, (void*)i);
		
	}
	
	//exit the threads
	pthread_exit(NULL);
		
}
