#pragma once

#include <sys/epoll.h>
#include <memory>
#include <unordered_map>
#include "HttpData.h"
#include "Timer.h"
#include <vector>
#include <unistd.h>

class ServerSocket;

int setNonBlocking(int fd);
class Epoll
{
public:
    static int MAX_EVENT_NUM; //系统的最大event
private:
//不需要记录event数量，因为epoll采用回调算法通知事件，复杂度为O(1)
    static Timer mTimer;
    std::unique_ptr<epoll_event[]> mEpollEvents;
    std::vector<std::shared_ptr<HttpData>> userData;    //这里可以改进为内存池
public:
    int mEpollFd;
    Epoll(int);
    void addFd(int fd,bool oneshot);
    void delFd(int fd);
    static void modFd(int epollFd,int fd,uint32_t ev);
    std::vector<std::shared_ptr<HttpData>> poll(ServerSocket&,int eventNum,int delay);
};
