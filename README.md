# Parallel-computing

## Introduction
Moor's Law forecasts that the number of transistors incorparated in a chip would approximately double every 24 months. Also when the number of transisters are increased the performace also increased. As a result of it older days performance depend only on the hardware. Not in the software level. Until the power wall is created. Then created architectures with shallow pipelines using less power. 

### Importance of parallel computing 
Consider creating a throughput using one core the amount of power required to generate the same throught put with two cores and half of the frequency of the single core provides less power consumption quantitatively the power requirement less than the 40% of the first. Therefore as a result we can see that multiple cores using lower frequencies now we able to generate the same throughput as single core processors but with low power. 

### Where the performance handled in nowadays.
In earlier implementations the performance is based on the hardware architecture, number of transisters in the CPU. But with the approach of the parallel programming concepts the performance handling is shifted into the hands in the software. Also automatic parallelization is inevitable according to the decade of researches. Therefore it would be necessary for parallalize the develop codes by the developers. 

### Key points to know 
* Concurency - A condition of a system in which multiple tasks are logically active at one time. 
* Parallelism - A codition of a system in which multiple tasks are actually active at a time. 
* Parallel programs - Subset of Concurrent Programs, Subset of Programs. 
* Concurrent Applications vs Parallel Applications 
* Concurrent Applications - An application for which computations logically execute simultaneously due to the semantics of the application. In here the problem is fundamentally concurrent. 
* Parallel Applications - An application for which the computations actually executes simultaneously in order to complete a problem in less time. In this case the problem does not inherently require concurrency. And you can state it sequentially as well. 

### Steps to implement the parallel program.
1. Analyse the parallelism in code and data. 
2. Understand the parallelism and assign into an algoritham. 
3. Using a parallel programing language implement. 

### Programming Language use
1. OpenMP (Multi Processor) - An API for writing multi threaded applications. A set of compiler directives and library routines for parallel application programmers. Greately simplifies writing multi-threaded (MT) programs in Fortran, C, and C++.
2. C# .net (comming soon)

### OpenMP Basic Definition : Solution Stack
* In the hardware layer there will be a shared memory space and processes will be using the shared resource. 
* In the system layer there will be openMP Runtime Library and OS/System support for shared memory and threading.
* In the program layer there will be Directives, Compiler, OpenMP library and Environment Variables.
* In the user layer there will be end user applications. 
* Most of the constructs in openMP based on compiler directives. Function prototypes and types in the file.  
```C
#pragma omp construct [clause [clause] .. ]
#pragma omp parallel num_threads(4)

#include <omp.h>
```
* OpenMP - Core Syntax - Most OpenMP constructs applied to a "Structured Block" (A block of one or more statements with one point of entry at the top and one point of exit at the bottom.  


