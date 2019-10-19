#include<stdio.h>

main()
{
	printf("Main Process ID : %d",getpid());
	printf("\n");
	printf("Main Process Parent ID : %d",getppid());
	printf("\n");
	int id;
	id = fork();
	
	if(id == 0)
	{
		printf("Child process has started\n\n");
		printf("Process ID : %d",getpid());
		printf("\n");
		printf("\nProcess Parent ID : %d",getppid());
		printf("\n");
		printf("\nChild process has ended\n\n");
	}
	
	else
	{
		printf("Parent process has started\n\n");
		printf("Process ID : %d",getpid());
		printf("\n");
		printf("Process Parent ID : %d",getppid());
		printf("\n");
		printf("Parent process is going to sleep\n\n");
		sleep(10);
		printf("\nParent process has woken up\n\n");
		printf("\nParent process has ended\n\n");
		//printf("Parent process has ended\n\n");
	}
	
	exit(0);
}
