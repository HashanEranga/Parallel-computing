#include <omp.h>
#include <stdio.h>
#define NUM_THREADS 64
#define PAD 8 

/*
    CO524 - Parallel Computing 
    Lab 01 - Introduction to Parallel Programming in OpenMP
    Lab Task - 02
    Creating Threads: calculate π in parallel using pragma omp parallel 
    Approach - Using the knowledge of cache lining 

    Running result
    
    1  thread  running time : 0.854 seconds
    2  threads running time : 0.476 seconds 
    4  threads running time : 0.235 seconds 
    8  threads running time : 0.149 seconds
    16 threads running time : 0.122 seconds
    32 threads running time : 0.126 seconds
    64 threads running time : 0.125 seconds

*/

int main(){
    unsigned long nsteps = 1<<27; 
    double dx = 1.0 / nsteps;
    double pi = 0.0;
    double start_time = omp_get_wtime();
    unsigned long i;
    int mainThreads;

    double sum[NUM_THREADS][PAD];

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
            sum[id][0] += 4.0 / (1.0 + x * x);
        } 
    }

    for(i = 0; i < mainThreads; i++){
        pi += sum[i][0] * dx;
    }

    double delta = omp_get_wtime() - start_time;

    printf("PI = %.16g computed in %.4g seconds with %d threads.", pi, delta, NUM_THREADS);
}
