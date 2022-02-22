#pragma once

#include <queue>
#include <vector>
#include <time.h>
#include <memory>

class HttpData;
struct TimeNode
{
    TimeNode(std::shared_ptr<HttpData>,size_t);
    bool isDeleted;
    size_t expiredTime;
    std::shared_ptr<HttpData> mUserData;
    static size_t currTime();           //ms
    void close();
};

struct TimeCompare
{
    bool operator()(const std::shared_ptr<TimeNode> a,const std::shared_ptr<TimeNode> b)
    {
        return a->expiredTime>b->expiredTime;
    }
};
class Timer
{
public:
    typedef std::shared_ptr<TimeNode> shared_TimeNode;
    shared_TimeNode addTimer(std::shared_ptr<HttpData> , size_t);
    size_t topTime();
    //void delTimer(shared_TimeNode);
    void tick();
private:
    //priority_queue选择用vector实现，连续内存，所以元素使用固定大小的指针
    std::priority_queue<shared_TimeNode,std::vector<shared_TimeNode>,TimeCompare> timeHeap;

};
