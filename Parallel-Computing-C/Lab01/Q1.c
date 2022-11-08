#include <omp.h> // use openMP libraries 
#include <stdio.h> // use standard input output libraries for c language

/*
    CO524 - Parallel Computing 
    Lab 01 - Introduction to Parallel Programming in OpenMP
    Lab Task - 01
    Display a very simple multi-threaded parallel program "Hello, world." written in C / C++
    / Fortran (you can choose the programming language according to your preference).
*/

int main(){
    // set number of threads for 1 to print "Hello world" using 1 thread
    omp_set_num_threads(1);

    // run settled number of threads in parallel 
    #pragma omp parallel   
    {
        // view the thread id 
        // int ID = omp_get_num_threads();
        // printf("Operating thread number is %d\n", ID);
        printf("hello, world\n"); // one thread will handle this print
    }
    return 0;
}

