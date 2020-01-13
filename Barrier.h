#ifndef BARRIER_H_
#define BARRIER_H_

#include <semaphore.h>

class Barrier {
public:
    Barrier(unsigned int num_of_threads);
    void wait();
	unsigned int waitingThreads();
    ~Barrier();

    sem_t * mutex;
    sem_t* barrier1;
    sem_t* barrier2;

	// TODO: define the member variables
	// Remember: you can only use semaphores!
};

#endif // BARRIER_H_

