# Parallel Computing using OpenMP in C
## Compile OpenMP in Linux with gcc
```C
>> gcc -fopenmp foo.c
>> ./a.out
```

## Creating a sample C program

### Sample Code 1 : Implement a code without OpenMP
```C
int main(){
    int ID = 0;
    printf("hello(%d)", ID);
    printf("world(%d)", ID);
    return 0;
}
```

### Sample Code 2 : Implement a code with OpenMP imported
```C
import <omp.h>
int main(){
    #pragma omp parallel{
        int ID = 0;
        printf("hello(%d)", ID);
        printf("world(%d)", ID);
    }

    return 0;
}
```
## Sample Code 3 : Implement a code example with OpenMP using in built functions 
```C
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
```

## Underline Hardware details about above sample codes
### Shared Memory Computers
Any computer composed of multiple processing elements that share an address space. There are two classes. 
1. Symmetric Multiprocessor (SMP)
2. Non Uniform Address Space Multiprocessor (NUMA)

### 01. Symmetric Multiprocessor (SMP)
A shared address space with "equal time" access for each processor, and the OS treats every processor the same way. 
Intel Core i7-970 Processor - Close to an SMP, have a shared address space. Because of the cache architecture, if there is a cache near to a processor it got faster access time compared to a far away one. 
### 02. Non Uniform Address Space Multiprocessor (NUMA)
Different memory regions have different access costs. Think of memory segmented into "near" and "far" memory. 

## Processes in OS
### Threads
Threads are lightweight processes
Threads are share process state among multiple threads. This greatly reduces the cost of switching context. 
### Process in a OS 
Contains Stack (stack pointer, program counter, registers), Text (program), Data (ProcessID, UserID, GroupID), Heap (Files, Locks, Sockets). This is a structure of a process. Each thread creates own program counter and registers from the stack and they share the Text region, Data region and the Heap. This is why modern OSs having shared memories have threads. 
### An instance of a program
One process lot of threads. Threads interact through read/write to a shared memory space. 
OS schedular decides when to run which threads. Interleaved for fairness. Synchronization to assure every legal order result in correct results.

### Reasons for Sample Code 3
Threads are interleaved with time. The programmar need to know use this to create correct results. This is the challenge in multithreaded programming. 

## OpenMP overview
OpenMP is a multi-threading, shared address model. Threads communicates by sharing variables. Unintended sharing of data causes race conditions. To control race conditions, use synchronization to protect data conflicts. Synchronization is expensive. 

### Race Conditions
When program's outcome changes as the threads are scheduled differently. 
