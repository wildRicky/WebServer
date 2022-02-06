#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <functional>
#include <vector>
#include <list>
#include "MutexLock.h"

const int MAX_THREAD_NUM=1024;
const int MAX_QUEUE_NUM=65535;

struct ThreadTask
{
    std::function<void (std::shared_ptr<void>)> process;
    std::shared_ptr<void> data;
};

class ThreadPool
{
public:
    static ThreadPool& getInstance(int threadNum,int maxRequestNum);
    static void worker();
    bool add(std::function<void (std::shared_ptr<void>)> fun,std::shared_ptr<void> arg);
private:
    ThreadPool(int threadNum,int maxRequestNum);
    ~ThreadPool();
    void run();
    //锁只是简单的保护队列，不需要复杂的操作，所以用最原始的pthread_mutex即可，不需要使用unique_lock，unique_guard,std::mutex等
    MutexLock poolMutex;
    Sem poolSem;
    std::vector<pthread_t> mThreads;
    std::list<ThreadTask> requestQueue;
    int mThreadNum;
    int mMaxRequestNum;
    bool mStop;
private:
    static void *worker(void*);
};
