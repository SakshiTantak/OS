#include<stdio.h>
#include<string.h>

int binarySearch(int[],int,int,int);

int main(int argc[], char* argv[])
{
	printf("\n\nProgram 2b_2.c begins!!\n\n");
	
	int a[15];
	int key,i;
	int valid;
	
	printf("\n\nEnter the number to be searched in the array : ");
	scanf("%d",&key);
	
	printf("\n\nCopying elements from argv[] into a[] by converting from alphabets to integers!!\n\n");
	
	for(i=0;i<argc;i++)
		a[i] = atoi(argv[i]);
		
	printf("\n\nBeginning binary search!!\n\n");
	
	valid = binarySearch(a,0,argc,key);
	
	if(valid != -1)
		printf("\n\n%d found at position : %d\n\n",key,valid);
		
		
	printf("\n\nProgram 2b_2 has ended!!\n\n");
	return 0;
	
}

int binarySearch(int arr[], int l, int r, int x) 
{ 
    int m;
    while (l <= r) 
    { 
        m = (l + r) / 2; 
   
        if (arr[m] == x) 
            return m; 
   
        else if (arr[m] < x) 
            l = m + 1; 
  
	    else
            r = m - 1; 
    } 
  
    printf("\n\n%d not found!!",x);
    return -1; 
} 
