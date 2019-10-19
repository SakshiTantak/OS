#Assignment 2(b)
#Class:TE-9
#Batch:K-9
#Roll no:33104
#Title:

#include<stdio.h>
#include<string.h>

void swap(int*, int*);
void bubbleSort(int[], int);

int main()
{
	printf("\n\nProgram 2b_1.c begins!!\n\n");
	
	int a[15],str[15];
	int i, n;
	int p_id;
	char* arg[15];
	printf("\n\nMain Process ID : %d",getpid());
	printf("\n\nMain Process Parent ID : %d",getppid());
	
	printf("\nEnter the number of elements in integer array : ");
	scanf("%d",&n);
	
	printf("\n\nAccepting integer array\n");
	for(i=0;i<n;i++)
	{
		printf("\nElement [%d] : ",i);
		scanf("%d",&a[i]);
	}
	
	printf("\n\nEntered integer array : [");
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
		
	printf("]\n");
	
	bubbleSort(a,n);	
	
	printf("\n\nInvoking Fork!\n");
	p_id = fork();
	
	printf("\n\nForked!!\n");
	
	if(p_id == 0)
	{
		printf("\n\nIn child process!!");
		printf("\n\nChild Process ID : %d",getpid());
		printf("\n\nChild Process Parent ID : %d",getppid());
		printf("\n\nSorted array is : [ ");
		for(int i=0;i<n;i++)
		{
			printf("%d ",a[i]);
			sprintf(str,"%d",a[i]);
			arg[i] = malloc(sizeof(str));
			strcpy(arg[i],str);
		}
		
		arg[i] = NULL;
		
		printf("]\n\n");
		
		printf("\nExecuting execve command!!\n\n");
		execve("./2b_2",arg,NULL);
		printf("\n\nexecve execution completed!!\n\n");
	}
	
	else
	{
		printf("\n\nIn parent process!!");
		printf("\n\nProcess ID : %d",getpid());
		printf("\n\nProcess Parent ID : %d",getppid());
		printf("\n\nParent process going into wait state!!");
		wait();
		printf("\n\nParent process is out of wait state!!");
		printf("\n\nParent process exits!!"); 
	}
	
	printf("\n\nProgram 2b_1 has ended!!\n\n");
	return 0;
}


void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  

void bubbleSort(int arr[], int n) 
{ 
	printf("\n\nBubble Sort beginning");
	printf("\n\nBubble Sort Process ID : %d",getpid());
	printf("\n\nBubble Sort Parent Process ID : %d",getppid());

    int i, j; 
  
    for (i = 0; i < n-1; i++)           
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
              
    printf("\n\nBubble Sort completed!!\n");
              
} 

