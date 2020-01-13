#include "Barrier.h"

Barrier::Barrier(unsigned int num_of_threads){
    this->numOfThreads=num_of_threads;
    this->countOfThreads=0;
    this->currentBarrierToUse=1;
    sem_init(this->mutex,0,1);
    sem_init(this->barrier1,0,0);
    sem_init(this->barrier2,0,0);
}

unsigned int Barrier::waitingThreads(){
return (this->currentBarrierToUse==1?
        (this->numOfThreads-this->countOfThreads):
        (this->countOfThreads));
}

void  Barrier::wait(){

}

Barrier::~Barrier(){
    sem_destroy(this->mutex);
    sem_destroy(this->barrier1);
    sem_destroy(this->barrier2);
}