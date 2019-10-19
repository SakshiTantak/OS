
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 

int main() 
{ 
    // ftok to generate unique key 
    key_t key = ftok(".",65); 
    void* sharedMem = (void*) 0;
  
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
    
  	char *str = (char*) shmat(shmid,(void*)0,0); 
  	sharedMem = shmat(shmid,(void*)0,0);
  	
  	if(sharedMem == (void*) -1)
  	{
  		printf("shmat failed!\n");
  		exit(0);
  	}
  	
  	else
  		printf("Memory attached at logical address %d\n",(int)sharedMem);
     
    
    printf("Write Data : "); 
    gets(str); 
  	
    printf("Data written in memory: %s\n",str); 
      
    //detach from shared memory  
    shmdt(str); 
  
    return 0; 
} 

