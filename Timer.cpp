#include "Timer.h"
#include <sys/time.h>
#include <exception>

static size_t TimeNode::currTime()
{
    struct timeval cur;
    gettimeofday(&cur,NULL);
    return cur.tv_sec*1000+cur.tv_usec/1000;
};

TimeNode::TimeNode(std::shared_ptr<HttpData> data,size_t delay):isDeleted(false),userData(data)
{
    expiredTime=delay*1000+currTime();
};

void Timer::addTimer(std::shared_ptr<HttpData> data,size_t delay)
{
    timeHeap.push(shared_TimeNode(TimeNode(data,delay));
    return;
}

void Timer::delTimer(shared_TimeNode node)
{
    node->isDeleted=true;
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
