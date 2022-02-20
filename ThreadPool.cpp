#include "ThreadPool.h"
#include <iostream>

ThreadPool& ThreadPool::getInstance(int threadNum,int maxRequestNum)
{
    static ThreadPool singleton(threadNum,maxRequestNum);
    return singleton;
}

void* ThreadPool::worker(void*)
{
    getInstance(0,0).run();
    return nullptr;
}

ThreadPool::ThreadPool(int threadNum,int maxRequestNum):mThreadNum(threadNum),
mMaxRequestNum(maxRequestNum),mStop(false)
{
    if(threadNum<=0||threadNum>MAX_THREAD_NUM)
        mThreadNum=128;
    if(maxRequestNum<=0||maxRequestNum>=MAX_QUEUE_NUM)
        mMaxRequestNum=2048;
    mThreads.resize(threadNum);
    std::cout<<"ThreadPool create : "<<mThreadNum<<std::endl;
    for(int i=0;i<mThreadNum;++i)
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

bool ThreadPool::add(std::shared_ptr<ThreadTask> fun)
{
    std::cout<<"add task to pool"<<std::endl;
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
        std::cout<<"sem avilable"<<std::endl;
        poolMutex.lock();
        std::cout<<"get pool lock"<<std::endl;
        if(requestQueue.empty())
        {
            poolMutex.unlock();
            continue;
        }
        auto task=requestQueue.front();
        requestQueue.pop_front();
        poolMutex.unlock();
        task->process(task->data);
    }
    return;
};
