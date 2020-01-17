#include "Barrier.h"
#include <iostream>

using namespace std;

Barrier::Barrier(unsigned int num_of_threads){
    numOfThreads=num_of_threads;
    countOfThreads=0;
    currentBarrierToUse=1;
    sem_init(&mutex,0,1);
    sem_init(&barrier1,0,0);
    sem_init(&barrier2,0,0);
}

unsigned int Barrier::waitingThreads(){
return (currentBarrierToUse==2?
        (numOfThreads-countOfThreads):
        (countOfThreads));
}

void  Barrier::wait(){
    switch(this->currentBarrierToUse){
        case 1:
            sem_wait(&mutex);
            if(++countOfThreads==numOfThreads){
                this->currentBarrierToUse=2;
                for(int i=0;i<numOfThreads;i++){
                    sem_post(&barrier1);
                }
            }
            sem_post(&mutex);
            sem_wait(&barrier1);
        case 2:
            sem_wait(&mutex);
            if(--countOfThreads==0){
                this->currentBarrierToUse=1;
                for(int j=0;j<this->numOfThreads;j++) {
                    sem_post(&barrier2);
                }
            }
            sem_post(&mutex);
            sem_wait(&barrier2);
    }

}

Barrier::~Barrier(){
    sem_destroy(&mutex);
    sem_destroy(&barrier1);
    sem_destroy(&barrier2);
}