#include<stdio.h>

void swap(int*, int*);
int partition(int[], int, int);
void quickSort(int[], int, int);
//void printArray(int[], int);
void mergeSort(int[], int, int);
void merge(int[], int, int, int); 

int main()
{
	int id;
	int arr1[10], arr2[10];
	int n1,n2;
	
	printf("\n\nMain Process ID : %d",getpid());
	printf("\n\nProcess Parent ID : %d",getppid());
	
	printf("\nBefore fork\n\n");
	printf("\n\nEnter 10 numbers for quick sort\n\n");
	for(int i=0;i<10;i++)
	{
		printf("\nNumber [%d] : ",i);
		scanf("%d",&arr1[i]);
	}
	
	printf("\n\nEnter 10 numbers for merge sort\n\n");
	for(int i=0;i<10;i++)
	{
		printf("\nNumber [%d] : ",i);
		scanf("%d",&arr1[i]);
	}	
	
	id=fork();
	
	printf("\nAfter fork\n\n");
	
	if(id==0)
	{
		printf("\n\nIn child process. Quick Sort begins\n\n");
		printf("\nQuick Sort (child)  Process ID : %d",getpid());
		printf("\nQuick Sort Parent Process ID : %d",getppid());
	
		n1 = sizeof(arr1) / sizeof(arr1[0]);
		
		quickSort(arr1,0,n1-1);
		printf("\n\nQuick Sorted array is : ");
    	for(int i=0;i<n1;i++)
    		printf("%d ",arr1[i]);
  
		printf("\n\nQuick Sort (child) ends\n\n");
	}
	
	else
	{
		printf("\n\nIn Parent Process. Merge Sort begins!\n\n");
		printf("\nMerge Sort (parent) Process ID  : %d",getpid());
		printf("\nMerge Sort (parent) Parent Process ID : %d",getppid());
		
		n2 = sizeof(arr2) / sizeof(arr2[0]);
		
		mergeSort(arr2,0,n2-1);
		printf("\nMerge Sorted array is : ");
    	for(int i=0;i<n2;i++)
    		printf("%d",arr2[i]);
    	
		printf("\n\nParent is going into wait state!\n\n");
		wait();
		printf("\n\nParent is out of wait state!\n\n");
		printf("\n\nParent ends!\n");
	}
	
	return 0;
}


void swap(int* a, int* b)  
{  
    int t = *a;  
    *a = *b;  
    *b = t;  
}  

int partition (int arr[], int low, int high)  
{  
    int pivot = arr[high]; // pivot  
    int i = (low - 1); // Index of smaller element  
  
    for (int j = low; j <= high - 1; j++)  
    {  
        // If current element is smaller than or  
        // equal to pivot  
        if (arr[j] <= pivot)  
        {  
            i++; // increment index of smaller element  
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  

void quickSort(int arr[], int low, int high)  
{  
    if (low < high)  
    {  
        /* pi is partitioning index, arr[p] is now  
        at right place */
        int pi = partition(arr, low, high);  
  
        // Separately sort elements before  
        // partition and after partition  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
    
    
}  
  
void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
  
        // Sort first and second halves 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
    
} 

void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2]; 
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
