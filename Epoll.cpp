#include "Epoll.h"
#include <unistd.h>
#include <iostream>
#include <exception>
#include "Socket.h"

int setNonBlocking(int fd)
{
    int oldOption=fcntl(fd,F_GETFL);
    int newOption=oldOption|O_NONBLOCK;
    fcntl(fd,F_SETFL,newOption);
    return oldOption;
}

Epoll::Epoll(int maxFdNum):userData(maxFdNum)
{
    mEpollFd=epoll_create(maxFdNum);       //最大连接数+connFd
    HttpData::epollFd=mEpollFd;
    for(int i=0;i<maxFdNum;++i)
    {
        userData[i]=std::make_shared<HttpData>();
    }
}
void Epoll::addFd(int fd,bool oneshot)
{
    epoll_event event;
    event.events=EPOLLIN|EPOLLET;
    if(oneshot)
        event.events|=EPOLLONESHOT;
    event.data.fd=fd;
    epoll_ctl(mEpollFd,EPOLL_CTL_ADD,fd,&event);
    setNonBlocking(fd);
    return;
}

void Epoll::modFd(int epollFd,int fd,_uint32_t ev)
{
    epoll_event event;
    event.events=ev|EPOLLET|EPOLLONESHOT;
    epoll_ctl(epollFd,EPOLL_CTL_MOD,fd,&event);
}

void Epoll::delFd(int fd)
{
    epoll_ctl(mEpollFd,EPOLL_CTL_DEL,fd,0);
    close(fd);
    return;
}

bool Epoll::poll(int listenFd,int eventNum,int delay)
{
    //epoll_wait的第二个参数见收藏夹
    int pollNum=epoll_wait(mEpollFd,mEpollEvents.get(),eventNum,delay);
    if(pollNum<0)
    {
        std::cout<<"epoll_wait error!"<<std::endl;
        return false; 
    }
    for(int i=0;i<pollNum;++i)
    {
        int sockfd=mEpollEvents[i].data.fd;
        if(sockfd==listenFd)    // 判断是否是监听套接字,listenFd没有设置成ONESHOT模式
        {
           sockaddr_in addr;
           socklen_t addrLen=sizeof(addr);
           int connFd=ServerSocket::accept(&addr);
           if(connFd<0)
           {
               perror("wrong connect");
               continue;
           }
           if(connFd>MAX_EVENT_NUM)
           {
               perror("server busy");
               continue;
           }
           //std::shared_ptr<HttpData> usrDataPtr=std::make_shared<HttpData>(addr,addrLen,connFd);
           userData[connFd].init(addr,addrLen,connFd);
           //加入定时器
           std::shared_ptr<TimeNode> timeNodePtr=mTimer.addTimer(usrData[connFd],300);
           usrData.setTimer(timeNodePtr);
           //userDataMap[connFd]=usrDataPtr;
           //加入Epoll队列
           addFd(connFd,true);
        }
        else if(mEpollEvents[i].events & (EPOLLRDHUP|EPOLLHUP|EPOLLERR))
        {
            // 关闭连接
            delFd(sockfd);
            userData[sockfd]->closeTime();
        }
        else if(mEpollEvents[i].events & EPOLLIN)
        {
            if(userData[sockfd]->mRequest->read())
            {
                //TODO 将任务加入ThreadPool queue
                mThreadpool.add(std::bind(HttpRequest::parseContent(),*(userDataMap[sockfd]->mRequest)));
            }
            else
            {
                delFd(sockfd);
                userData[sockfd]->closeTime();
            }
        }
        else if(mEpollEvents[i].events & EPOLLOUT)
        {
            //将响应发送给用户
            if(!userData[sockfd]->write())
            {
                delFd(sockfd);
                userData[sockfd]->closeTime();
            }
        }
    }
    return true;
}
