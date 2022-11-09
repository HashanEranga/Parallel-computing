#include <omp.h>
#include <stdio.h>
#define NUM_THREADS 64

/*
    CO524 - Parallel Computing 
    Lab 01 - Introduction to Parallel Programming in OpenMP
    Lab Task - 02
    Creating Threads: calculate π in parallel using pragma omp parallel

    Algorithm Strategy used : Synchronization Critical section

    Running result
    
    1  thread  running time : 0.829 seconds
    2  threads running time : 0.429 seconds 
    4  threads running time : 0.232 seconds 
    8  threads running time : 0.136 seconds
    16 threads running time : 0.107 seconds
    32 threads running time : 0.103 seconds
    64 threads running time : 0.113 seconds

*/

int main(){
    unsigned long nsteps = 1<<27; 
    double dx = 1.0 / nsteps;
    double pi = 0.0;
    double start_time = omp_get_wtime();
    unsigned long i;
    int mainThreads;

    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel 
    {
        int i, id, subThreads;
        double x, sum = 0.0;
        id = omp_get_thread_num();
        subThreads = omp_get_num_threads();
        if(id == 0) mainThreads = subThreads;

        for(int i=id; i< nsteps; i = i+subThreads){
            x = (i + 0.5) * dx;
            sum += 4.0 / (1.0 + x * x);
        } 
        sum = sum * dx;
        #pragma omp atomic 
            pi += sum;

    }

    double delta = omp_get_wtime() - start_time;

    printf("PI = %.16g computed in %.4g seconds with %d threads.", pi, delta, NUM_THREADS);
}
