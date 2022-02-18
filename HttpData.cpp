#include "HttpData.h"
#include <memory>
#include "Timer.h"
#include <windows.h>
void HttpData::closeTime()
{
    if(!mTimer.expired())
    {
        mTimer->close();
        
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
    mRequest.init();
    return;
}

bool HttpData::write()
{
    std::string response= mResponse->setResponse();
    int size=response.size();
    if(size==0)
    {
        modFd(HttpData::epollFd,mClientSocket->sockfd,EPOLLIN);
        return true;
    }
    char *buff=response.c_str();
    int writeIndex=0,sockFd=mClientSocket->sockfd;
    while(1)
    {
        temp=writev(sockFd,buff,size);
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
            modfd(HttpData::mEpollFd,sockFd,EPOLLIN);
            return true;
        }
    }
}
