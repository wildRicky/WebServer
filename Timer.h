#pragma once

#include <priority_queue>
#include <vector>
#include <time.h>
#include <memory>

class HttpData;
struct TimeNode
{
    TimeNode(std::shared_ptr<HttpData>,size_t);
    ~TimeNode();
    bool isDeleted;
    size_t expiredTime;
    std::shared_ptr<HttpData> userData;
    static size_t currTime();           //ms
}

struct TimeCompare
{
    bool operator()(const TimeNode &a,const TimeNode &b)
    {
        return a.expiredTime<b.expiredTime;
    }
}
class Timer
{
public:
    typedef std::shared_ptr<TimeNode> shared_TimeNode;
    void addTimer(std::shared_ptr<HttpData>,size_t delay);
    void delTimer(shared_TimeNode);
    void tick();
private:
    //priority_queue选择用vector实现，连续内存，所以元素使用固定大小的指针
    std::priority_queue<shared_TimeNode,vector<shared_TimeNode>,TimeCompare> timeHeap;

}
