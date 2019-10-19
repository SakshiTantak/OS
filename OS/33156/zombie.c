#include<stdio.h>

main()
{
	int id;
	printf("\nBefore fork\n\n");
	id = fork();
	printf("After fork\n\n");
	
	if(id != 0)
	{
		printf("Parent process has started\n\n");
		printf("Process ID : %d",getpid());
		printf("\n\n");
		printf("Process parent ID : %d",getppid());
		printf("\n\n");
		printf("Parent is going to sleep\n\n");
		sleep(10);
		printf("Parent has woken up!\n\n");
		while(1)
		{//infinite loop
		}
		
		exit(0);
	}
	
	else
	{
		printf("Child process has started!\n\n");
		printf("Process ID : %d",getpid());
		printf("\n\n");
		printf("Process parent ID : %d",getppid());
		printf("\n\n");
		printf("Child is going to die!\n\n");
		exit(0);
		
	}
}
