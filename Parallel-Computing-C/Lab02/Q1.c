#include <stdlib.h>   
#include <stdio.h>    
#include <omp.h>      

#define ARRAY_SIZE 8   
#define NUM_THREADS 4  

int main (int argc, char *argv[]) 
{
	int * arr1;
	int * arr2; 
	int * arrSum;
        
    int n = ARRAY_SIZE;                 
	int n_per_thread;                   
	int total_threads = NUM_THREADS;    
	int i;       
        
    arr1 = (int *) malloc(sizeof(int)*n);
	arr2 = (int *) malloc(sizeof(int)*n);
	arrSum = (int *) malloc(sizeof(int)*n);

	for(i=0; i<n; i++) {
		arr1[i] = i;
	}

	for(i=0; i<n; i++) {
		arr2[i] = i;
	}   
	
	omp_set_num_threads(total_threads);
	
	n_per_thread = n/total_threads;
	
	#pragma omp parallel for shared(arr1, arr2, arrSum) private(i) schedule(static, n_per_thread)
        for(i=0; i<n; i++) {
			arrSum[i] = arr1[i]+arr2[i];
			printf("Thread %d works on element%d\n", omp_get_thread_num(), i);
        }
	
		printf("i\ta[i]\t+\tb[i]\t=\tc[i]\n");
			for(i=0; i<n; i++) {
			printf("%d\t%d\t\t%d\t\t%d\n", i, arr1[i], arr2[i], arrSum[i]);
			}
			free(arr1);  free(arr2); free(arrSum);
	return 0;
}