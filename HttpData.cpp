#include "HttpData.h"
#include <memory>
#include "Timer.h"
#include <unistd.h>
#include <HttpRequest.h>
#include <HttpResponse.h>
#include <Socket.h>
#include <sys/socket.h>
#include "Epoll.h"
#include <iostream>

int HttpData::epollFd=-1;
void HttpData::closeTime()
{
    if(!mTimer.expired())
    {
        mTimer.lock()->close();
        
    }
    return;
}
void HttpData::setTimer(std::shared_ptr<TimeNode> newTimer)
{
    closeTime();
    mTimer=newTimer;
    return;
}

void HttpData::init(sockaddr_in addr,socklen_t len,int connFd)
{
    mClientSocket=std::make_shared<ClientSocket>(addr,len,connFd);
    //mRequest是随线程池提前创建好的，需要初始化
    mRequest->init();
    return;
}

bool HttpData::write()
{   
    
    std::cout<<"begin write!"<<std::endl;
    std::string response= mResponse->setResponse();
    std::cout<<"Response : "<<response<<std::endl;
    int size=response.size();
    if(size==0)
    {
        Epoll::modFd(HttpData::epollFd,mClientSocket->sockFd,EPOLLIN);
        return true;
    }
    const char *buff=response.c_str();
    int writeIndex=0,sockFd=mClientSocket->sockFd;
    while(1)
    {
        int temp=::write(sockFd,buff,size);
        if(temp<=-1)
        {
            if(errno==EAGAIN)
            {   
                //io写入速度太慢，导致没有写空间，则继续等待下一轮EPOLLOUT事件
                //可以保证连接的完整性，但是无法接受客户端请求
                //modfd(HttpData::mEpollFd,sockFd,EPOLLOUT);
                //return true;
                sleep(1);
                continue;
            }
            return false;
        }
        writeIndex+=temp;
        size-=temp;
        if(size==0)
        {
            Epoll::modFd(HttpData::epollFd,sockFd,EPOLLIN);
            return true;
        }
    }
}
