#include <omp.h>
#include <stdio.h>
#define NUM_THREADS 1

/*
    CO524 - Parallel Computing 
    Lab 01 - Introduction to Parallel Programming in OpenMP
    Lab Task - 02
    Creating Threads: calculate π in parallel using pragma omp parallel

    Algorithm Strategy used : SPMD (Single Program Multiple Duplicates)
    Used round robin method to devide a portion of the iteration to the single thread. 
    For having the sum variables 
    mainThreads ask for how many threads were used in the calculations because when given number of threads will be less for limiting issues. 

    Running result
    
    1  thread  running time : 0.854 seconds
    2  threads running time : 1.376 seconds 
    4  threads running time : 1.204 seconds 
    8  threads running time : 0.88  seconds
    16 threads running time : 0.623 seconds
    32 threads running time : 0.497 seconds
    64 threads running time : 0.334 seconds

    There may have chance that the single thread option of the sequential program may take more time. 
    That is because they will be taking time for thread environment creation and thread creation as a result consume time.
    But according to the results of the running times of the program it should be more efficient. 
    Reason for this called false sharing 
*/

int main(){
    unsigned long nsteps = 1<<27; 
    double dx = 1.0 / nsteps;
    double pi = 0.0;
    double start_time = omp_get_wtime();
    unsigned long i;
    int mainThreads;

    double sum[NUM_THREADS];

    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel 
    {
        int i, id, subThreads;
        double x;
        id = omp_get_thread_num();
        subThreads = omp_get_num_threads();
        if(id == 0) mainThreads = subThreads;

        for(int i=id; i< nsteps; i = i+subThreads){
            x = (i + 0.5) * dx;
            sum[id] += 4.0 / (1.0 + x * x);
        } 
    }

    for(i = 0; i < mainThreads; i++){
        pi += sum[i] * dx;
    }

    double delta = omp_get_wtime() - start_time;

    printf("PI = %.16g computed in %.4g seconds with %d threads.", pi, delta, NUM_THREADS);
}
