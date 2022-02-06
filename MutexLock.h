#pragma once

#include <pthread.h>
#include <semaphore.h>
#include <exception>
class MutexLock
{
private:
    pthread_mutex_t mMutex;
public:
    MutexLock(){
        if(pthread_mutex_init(&mMutex,nullptr)!=0)
            throw std::exception();
    }
    ~MutexLock(){
        pthread_mutex_destroy(&mMutex);
    }
    void lock(){
        if(pthread_mutex_lock(&mMutex)!=0)
            throw std::exception();
        return;
    }
    void unlock()
    {
        if(pthread_mutex_unlock(&mMutex)!=0)
            throw std::exception();
        return;
    }
};

class Sem
{
private:
    sem_t mSem;
public:
    Sem()
    {
        if(sem_init(&mSem,0,0)!=0)
            throw std::exception();
    }
    ~Sem()
    {
        sem_destroy(&mSem);
    }
    void wait()
    {
        if(sem_wait(&mSem)!=0)
            throw std::exception();
    }
    void post()
    {
        if(sem_post(&mSem)!=0)
            throw std::exception();
    }
};
