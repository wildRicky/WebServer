#pragma once

#include <sys/epoll.h>
#include <memory>
#include <unordered_map>
#include "HttpData.h"

int setNonBlocking(int fd);
class Epoll
{
private:
    static const int MAX_EVENT_NUM; //系统的最大event
//不需要记录event数量，因为epoll采用回调算法通知事件，复杂度为O(1)
    int mEpollFd;
    std::unique_ptr<epoll_event[]> mEpollEvents;
    std::unordered_map<int,HttpData> userData;
public:
    void addFd(int fd);
    void delFd(int fd);
    void poll(int eventNum,int delay);
};
