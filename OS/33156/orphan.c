#include<stdio.h>

main()
{
	int id;
	printf("\n\n");
	printf("Before fork\n\n");
	printf("Main Process ID : %d",getpid());
	printf("\n\n");
	printf("Main Process Parent ID : %d",getppid());
	printf("\n\n");
	id = fork();
	
	printf("After fork\n\n");
	
	if(id != 0)
	{
		printf("Parent process has started!\n\n");
		printf("Process ID : %d",getpid());
		printf("\n\n");
		printf("Process Parent ID : %d",getppid());	
		printf("\n\n");
		printf("Parent process is going to sleep\n\n");
		sleep(10);
		printf("Parent process has woken up\n\n");
		printf("Parent is ending\n\n");
		exit(-1);	
	}
	
	else
	{
		printf("Child process has started!\n\n");
		printf("Process ID : %d",getpid());
		printf("\n\n");
		printf("Process Parent ID : %d",getppid());	
		printf("\n\n");
		printf("Child is going to sleep\n\n");
		sleep(10);
		sleep(15);
		printf("Child has woken up\n\n");
		printf("Child has been orphaned! New Parent ID : %d",getppid());
		exit(0);
	}
}
