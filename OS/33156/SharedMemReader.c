
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
  
int main() 
{ 
    // ftok to generate unique key 
    key_t key = ftok(".",65);
    int sharedMem = (void*) 0; 
  
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 
    char *str = (char*) shmat(shmid,(void*)0,0); 
    sharedMem = shmat(shmid,(void*)0,0);
    
    if(sharedMem == (void*) -1)
  	{
  		printf("shmat failed!\n");
  		exit(0);
  	}
  	
  	else
  		printf("Memory attached at logical address %d\n",(int)sharedMem);
     
    
  
    printf("Data read from memory: %s\n",str); 
      
    //detach from shared memory  
    shmdt(str); 
    
    // destroy the shared memory 
    shmctl(shmid,IPC_RMID,NULL); 
     
    return 0; 
} 

