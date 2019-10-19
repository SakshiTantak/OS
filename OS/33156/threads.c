#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* multiply(void*);
void initMatrix(int[3][3]);
void printMatrix(char, int[3][3]);
void inputMatrix(char, int [3][3]);

int A[3][3],B[3][3],C[3][3];

int main()
{
	printf("\n\nMain Thread initialised and started!!\n");
	int A[3][3],B[3][3],C[3][3];
	
	int i,j,k;
	int sum = 0;
	
	//initialise matrix A and B
	printf("\n\nInitialising matrix A\n");
	initMatrix(A);
	inputMatrix('A',A);
	printMatrix('A',A);
	
	printf("\n\nInitialising matrix B\n");
	initMatrix(B);
	inputMatrix('B',B);
	printMatrix('B',B);
	
	printf("\n\nInitialising matrix C\n");
	initMatrix(C);
	printMatrix('C',C);
	
	pthread_t t;
	
	pthread_create(&t,NULL,multiply,NULL);
	
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			for(k=0;k<3;k++)
			{
				printf("\n\nThread [%d][%d] started!\n",i,j);
				C[i][j] += A[i][k] * B[k][j];
				printf("\n\nThread [%d][%d] is going to sleep!\n",i,j);
				sleep(10);
				printf("\n\nThread [%d][%d] has woken up!\n",i,j);
			}	
		
	pthread_join(t,NULL);
	
	printMatrix('C',C);
	
	printf("\nThankyou!\n\n");
	return 0;
}

void initMatrix(int a[3][3])
{
	int i,j;
	
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			a[i][j] = 0;
}

void* multiply(void* para)
{
	int i,j,k;
	
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			for(k=0;k<3;k++)
				C[i][j] += A[i][k] * B[k][j];			
}

void printMatrix(char matName, int a[3][3])
{
	int i,j;
	
	printf("\n\nMatrix %c = ",matName);
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
			printf("%d\t",a[i][j]);
		printf("\n");
	}	
	printf("\nThread has ended!\n");
	pthread_exit(NULL);
}

void inputMatrix(char matName, int a[3][3])
{
	printf("\n\nInput Elements for matrix %c",matName);
	int i,j;
	
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
		{
			printf("\n%c[%d][%d] = ",matName,i,j);
			scanf("%d",&a[i][j]);
		}
}
