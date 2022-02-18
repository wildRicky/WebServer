#include "ThreadPool.h"
#include <iostream>

ThreadPool& ThreadPool::getInstance(int threadNum,int maxRequestNum)
{
    static ThreadPool singleton(threadNum,maxRequestNum);
    return singleton;
}

void ThreadPool::worker()
{
    getInstance(0,0).run();
    return;
}

ThreadPool::ThreadPool(int threadNum,int maxRequestNum):mThreadNum(threadNum),
mMaxRequestNum(maxRequestNum),mStop(false)
{
    if(threadNum<=0||threadNum>MAX_THREAD_NUM)
        mThreadNum=128;
    if(maxRequestNum<=0||maxRequestNum>=MAX_QUEUE_NUM)
        mMaxRequestNum=2048;
    mThreads.resize(threadNum);
    for(int i=0;i<threadNum;++i)
    {
        if(pthread_create(&mThreads[i],nullptr,worker,nullptr)!=0)
            throw std::exception();
        if(pthread_detach(mThreads[i])!=0)
            throw std::exception();
    }
    return;
};

ThreadPool::~ThreadPool()
{
    
};

bool ThreadPool::add(std::function<void ()> fun)
{
    if((int)requestQueue.size()==mMaxRequestNum)
    {
        std::cout<<"error!Request queue full"<<std::endl;
        return false;
    }
    //ThreadTask task;
    //task.process=fun;
    poolMutex.lock();
    requestQueue.push_back(fun);
    poolMutex.unlock();
    poolSem.post();
    return true;
};

void ThreadPool::run()
{
    while(!mStop)
    {
        poolSem.wait();
        poolMutex.lock();
        if(requestQueue.empty())
        {
            poolMutex.unlock();
            continue;
        }
        std::function<void()> process=requestQueue.front();
        requestQueue.pop_front();
        poolMutex.unlock();
        process();
    }
    return;
};
