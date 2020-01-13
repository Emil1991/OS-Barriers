#ifndef BARRIER_H_
#define BARRIER_H_

#include <semaphore.h>

class Barrier {
public:
    Barrier(unsigned int num_of_threads);
    void wait();
	unsigned int waitingThreads();
    ~Barrier();

    unsigned int numOfThreads;
    unsigned int countOfThreads;
    unsigned int currentBarrierToUse;
    sem_t * mutex;
    sem_t* barrier1;
    sem_t* barrier2;

};

#endif // BARRIER_H_

