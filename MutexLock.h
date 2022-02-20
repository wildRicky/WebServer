#pragma once

#include <pthread.h>
#include <semaphore.h>
#include <exception>
#include <iostream>

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
        std::cout<<"lock mutex"<<std::endl;
        return;
    }
    void unlock()
    {
        if(pthread_mutex_unlock(&mMutex)!=0)
            throw std::exception();
        std::cout<<"unlock mutex"<<std::endl;
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
        std::cout<<"semaphore init"<<std::endl;
    }
    ~Sem()
    {
        sem_destroy(&mSem);
        std::cout<<"semaphore destroy"<<std::endl;
    }
    void wait()
    {
        if(sem_wait(&mSem)!=0)
            throw std::exception();
        std::cout<<"semaphore wait"<<std::endl;
    }
    void post()
    {
        if(sem_post(&mSem)!=0)
            throw std::exception();
        std::cout<<"semaphore post"<<std::endl;
    }
};
