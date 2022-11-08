#include <omp.h>
#include <stdio.h>
#define NUM_THREADS 1

/*
    CO524 - Parallel Computing 
    Lab 01 - Introduction to Parallel Programming in OpenMP
    Lab Task - 02
    Creating Threads: calculate π in parallel using pragma omp parallel
*/

int main(){
    // A simple serial C code to calculate π is the following
    unsigned long nsteps = 1<<27; /* around 10^8 steps */
    double dx = 1.0 / nsteps;
    double pi = 0.0;
    double start_time = omp_get_wtime();
    unsigned long i;
    
    for (i = 0; i < nsteps; i++)
    {
        double x = (i + 0.5) * dx;
        pi += 1.0 / (1.0 + x * x);
    }
    pi *= 4.0 * dx;

    double delta = omp_get_wtime() - start_time;

    printf("PI = %.16g computed in %.4g seconds with %d threads.", pi, delta, NUM_THREADS);
}

/*
    Running result
    
    Sequential running time : 1.529 seconds
*/