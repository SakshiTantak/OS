#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

long int pos = 0;

int main()
{
	int fd1[2];
	int fd2[2];
	char* path1 = NULL;
	path1 = "ref.txt";	//path of file to read from
	pid_t id;			//variable for fork
	char cbuf[450];		//child buffer
	char pbuf[450];		//parent buffer
	
	if(pipe(fd1) == -1)		//create pipe 1
	{
		printf("\nPipe 1 failed!");
		return 1;
	}
	
	if(pipe(fd1) == -1)		//create pipe 2
	{
		printf("\nPipe 2 failed!");
		return 1;
	}
	
	printf("\nBefore Fork\n");
	id = fork();		//fork
	//printf("\nAfter Fork\n");
	
	if(id<0)				//check fork
	{
		printf("\nFork unsuccessful!");
		return 1;
	}
	
	else if(id>0)			//parent process
	{
		printf("\nFork successful! Inside parent!");
		close(fd1[0]);		//close read end of pipe 1 to use its write end
		printf("\nRead end of pipe 1 closed in parent!");
		write(fd1[1],&path1,strlen(path1));		//write path to write end of pipe 1
		printf("\nWritten %ld characters to pipe 1 : %s",strlen(path1),path1);
		//printf("\nWrite end of pipe1 closed!");		//finished writing, close write end of pipe 1
		close(fd1[1]);
		
		//printf("\nParent waiting for child to return!");	
		sleep(10);			//parent waits for child
		
		printf("\nReturned from child process!");
		close(fd2[1]);		//close write end of pipe 2 to use read end
		printf("\nWrite end of pipe 2 closed in parent!");
		read(fd2[0],pbuf,strlen(cbuf));		//read from read end of pipe 2
		printf("\nRead %ld characters from read end of pipe 2 : %s",strlen(pbuf),pbuf);
		//close(fd2[0]);							//close read end of pipe 2 since reading finished
		//printf("\nRead end of pipe 2 closed!\n");
				
	}	
	
	else if(id == 0)		//child process
	{
		FILE* fp = NULL;	//file pointer to open file of specified path
		char* path2 = NULL;
		printf("\n\nFork successful! Inside child!");
		close(fd1[1]);			//close write end of pipe 1 to use read end
		printf("\nWrite end of pipe 1 closed in child!");
		read(fd1[0],&path2,strlen(path1));		//read path from read end of pipe 1
		printf("\nRead %ld characters from read end of pipe 1 : %s",strlen(path1),path2);
		close(fd1[0]);							//close read end of pipe 1
		close(fd2[0]);
		printf("\nRead end of pipe 1 and pipe 2 closed!\n");
		fp = fopen(path2,"r");					//open file
		//fseek(fp,pos,0);						//seek to the left off position
		//printf("\nHI");
		//int z = rand() % 10 + 1;					//generate a random number
		int i = 0;
		printf("\nReading from file\n");
		while(!feof(fp))
		{
			cbuf[i] = getc(fp);
			printf("%c",cbuf[i]);
			i++;
		}
		printf("\n");
		i--;
		cbuf[i] = '\0';
		write(fd2[1],cbuf,i);
		printf("\nWritten %ld characters to write end of pipe 2 : %s\n",strlen(cbuf),cbuf);
		//pos = ftell(fp);						//store left off positon in pos
		close(fd2[1]);							//close write end of pipe 2
		printf("\nWrite end of pipe 2 closed!\n");
	}
	
	return 0;
}
