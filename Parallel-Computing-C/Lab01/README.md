# CO524 - Parallel Computing 
## Lab 01 - Introduction to Parallel Programming in OpenMP
### Lab Task - 01
Display a very simple multi-threaded parallel program "Hello, world." written in C / C++
/ Fortran (you can choose the programming language according to your preference).

#### set number of threads for 1 to print "Hello world" using 1 thread
```C
#include <omp.h> 
#include <stdio.h>

int main(){
    omp_set_num_threads(1);
    #pragma omp parallel   
    {
        int ID = omp_get_num_threads();
        printf("Operating thread number is %d\n", ID);
        printf("hello, world\n"); // one thread will handle this print
    }
    return 0;
}
```
### Lab Task - 02
Creating Threads: calculate π in parallel using pragma omp parallel

#### Sequential Approach of calculating pi
```C
#include <omp.h>
#include <stdio.h>
#define NUM_THREADS 1

int main(){
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
```

#### Creating Threads: calculate π in parallel using pragma omp parallel using Algorithm Strategy : SPMD (Single Program Multiple Duplicates)
Used round robin method to devide a portion of the iteration to the single thread. For having the sum variables 
mainThreads ask for how many threads were used in the calculations because when given number of threads will be less for limiting issues. 

```C
#include <omp.h>
#include <stdio.h>
#define NUM_THREADS 1

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

```

##### Running Times 
| Number of Threads | Runtime(seconds) | 
| ----------------- | :--------------: |
| 1 | 0.854 | 
| 2 | 1.376 |
| 4 | 1.204 |
| 8 | 0.880 |
| 16 | 0.623 | 
| 32 | 0.497 | 
| 63 | 0.334 | 

There may have chance that the single thread option of the sequential program may take more time. 
That is because they will be taking time for thread environment creation and thread creation as a result consume time.
But according to the results of the running times of the program it should be more efficient. 
Reason for this called false sharing