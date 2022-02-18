#include "Timer.h"
#include <sys/time.h>
#include <exception>

static size_t TimeNode::currTime()
{
    struct timeval cur;
    gettimeofday(&cur,NULL);
    return cur.tv_sec*1000+cur.tv_usec/1000;
};

TimeNode::TimeNode(std::shared_ptr<HttpData> usrDataPtr,size_t delay):isDeleted(false),mUserData(usrDataPtr)
{
    expiredTime=delay*1000+currTime();
};

shared_TimeNode Timer::addTimer(std::shared_ptr<HttpData> usrDataPtr,size_t delay)
{
    shared_TimeNode tmp=std::make_shared<TimeNode>(usrDataPtr,delay);
    timeHeap.push(tmp);
    return tmp;
}

void TimeNode::close()
{
    isDeleted=true;
    //这里HttpData只有timer引用，所以reset会使HttpData自动析构
    mUserData->reset();
    return;
}
size_t Timer::topTime()
{
    return timeHeap.top()->expiredTime;
}
void Timer::tick()
{
    size_t cur=TimeNode::currTime();
    while(!timeHeap.empty())
    {
        auto tmp=timeHeap.top();
        if(tmp->expiredTime>cur)
            break;
        if(!tmp->isDeleted)
            ;//調用刪除函數,删除epoll上的非活动连接
        timeHeap.pop();
    }
    return;
}
