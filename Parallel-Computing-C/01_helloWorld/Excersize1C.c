#include <omp.h>
#include <stdio.h>

int main(){
    #pragma omp parallel // this requests to give some number of threads  
    {
        int ID = omp_get_thread_num(); // this built in function returns the id value of the thread
        printf("hello(%d)", ID);
        printf("world(%d)", ID);
    }
    return 0;
}