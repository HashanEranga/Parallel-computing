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

### False Sharing 
If independent data elements happen to sit on the same cache line, each update will cause the cache line to "slosh back and forth" between threads. This is called false sharing. 
Shared last level cache and connection to I/O and DRAM. 
If you promote scalars to an array to support the creation of an SPMD program, the array elements are contiguous in memory hense share cache lines. This results poor scalability. 

### Avoiding false sharing 
1. Using the knowledge of the cache lining in the processor. 
2. Using synchronization without the hardware knowledge about cache lining. 

### 1. Using the knowledge of the cache lining in the processor.
Following solution will be improved by knowing the number of cache lining 
```C
#include <omp.h>
#include <stdio.h>
#define NUM_THREADS 64
#define PAD 8 

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

```
##### Running Times 
| Number of Threads | Runtime(seconds) | 
| ----------------- | :--------------: |
| 1 | 0.854 | 
| 2 | 0.476 |
| 4 | 0.235 |
| 8 | 0.149 |
| 16 | 0.122 | 
| 32 | 0.126 | 
| 63 | 0.125 | 

### 2. Using synchronization without the hardware knowledge about cache lining. 
In synchronization there are two flavours called. 
1. Barries Synchronization - Each thread wait at the barrier until all threads arrive. 
2. Mutual Exclusion - Define a block of code that only one thread at a time can execute. 

## Synchronization Implemetation 
1. Critical Construct 
2. Atomic Construct 
3. Barrier Construct

### Barrier Construct (This will be used for barrier synchronizations)
Defines a point in the program and say "all threads must arrive here before any thread go on". Observe the following example. 
```C
#pragma omp parallel
{
    int id = omp_get_thread_num();
    A[id] = big_cal1(id);
    #pragma omp barrier 
    B[id] = big_cal2(id, A);
}
```
Please Note that the big_cal1 and big_cal2 must be big calculations. Since A array will be used in the next calculation therefore need to put up a barrier there.  

### Critical Section Construct (Thiss will be used for mutual exclusion)
When move along the program if one occurs a critical section it will be done only one thread will be allowed. 
```C
#pragma omp parallel 
{
    float B;
    int i, id, nthrds;
    id = omp_get_thread_num();
    nthrds = omp_get_num_threads();
    for(i=id; i<niters; i+=nthrds){
        B = big_job(i);
    #pragma critical section
        res += consume(B);
    }
}
```
Be more caucious when creating critical section it will make the code serialized. 

### Atomic Construct 
Certain constructs presents in the hardware give quick updates of values in memory. Because achieve low level computations in low level runtime need the efficiency. In atomic of those hardware constructs are available they will be used. 
```C
#pragma omp parallel 
{
    double tmp, B;
    B = DOIT();
    tmp = big_ugly(B);

    #pragma omp atomic 
    X+=tmp; 
}
```
The statement inside the atomic must be one of the following forms. x binops=expr, x++, x--, ++x, --x