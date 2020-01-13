#include "Barrier.h"
#define WAIT(SEM) ({\
__typeof(SEM) sem=(SEM);\
sem_wait(&sem);\
})
#define SIGNAL(SEM) ({\
__typeof(SEM) sem=(SEM);\
sem_post(&sem);\
})



Barrier::Barrier(unsigned int num_of_threads){
    this->numOfThreads=num_of_threads;
    this->countOfThreads=0;
    this->currentBarrierToUse=1;
    sem_init(&mutex,0,1);
    sem_init(&barrier1,0,0);
    sem_init(&barrier2,0,0);
}

unsigned int Barrier::waitingThreads(){
return (this->currentBarrierToUse==2?
        (this->numOfThreads-this->countOfThreads):
        (this->countOfThreads));
}

void  Barrier::wait(){
    switch(this->currentBarrierToUse){
        case 1:
            WAIT(this->mutex);
            this->countOfThreads++;
            if(this->countOfThreads==this->numOfThreads){
                for(int i=0;i<this->numOfThreads;i++)
                    SIGNAL(barrier1);
                this->currentBarrierToUse=2;
            }
            SIGNAL(mutex);
            WAIT(barrier1);
            break;
        case 2:
            WAIT(mutex);
            this->countOfThreads--;
            if(this->countOfThreads==0){
                for(int j=0;j<this->numOfThreads;j++)
                    SIGNAL(barrier2);
                this->currentBarrierToUse=1;
            }
            SIGNAL(mutex);
            WAIT(barrier2);
            break;
    }
}

Barrier::~Barrier(){
    sem_destroy(&mutex);
    sem_destroy(&barrier1);
    sem_destroy(&barrier2);
}