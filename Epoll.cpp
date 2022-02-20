#include "Epoll.h"
#include <iostream>
#include <exception>
#include "Socket.h"
#include <fcntl.h>
#include "HttpRequest.h"
int Epoll::MAX_EVENT_NUM=1000;
Timer Epoll::mTimer=Timer();
int setNonBlocking(int fd)
{
    int oldOption=fcntl(fd,F_GETFL);
    int newOption=oldOption|O_NONBLOCK;
    fcntl(fd,F_SETFL,newOption);
    return oldOption;
}

Epoll::Epoll(int maxFdNum):userData(maxFdNum),mEpollEvents(new epoll_event[maxFdNum])
{
    std::cout<<"Epoll create"<<std::endl;
    if((mEpollFd=epoll_create(maxFdNum))<0)       //最大连接数+connFd
    {
        std::cout<<"Epoll create failed"<<errno<<std::endl;
        throw std::exception();
    }
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

void Epoll::modFd(int epollFd,int fd,uint32_t ev)
{
    epoll_event event;
    event.data.fd=fd;
    event.events=ev|EPOLLET|EPOLLONESHOT;
    epoll_ctl(epollFd,EPOLL_CTL_MOD,fd,&event);
}

void Epoll::delFd(int fd)
{
    epoll_ctl(mEpollFd,EPOLL_CTL_DEL,fd,0);
    close(fd);
    return;
}

std::vector<std::shared_ptr<HttpData>> Epoll::poll(ServerSocket &server,int eventNum,int delay)
{
    std::vector<std::shared_ptr<HttpData>> result;
       //epoll_wait的第二个参数见收藏夹
    std::cout<<"epoll_wait begin"<<std::endl;
    int pollNum=epoll_wait(mEpollFd,mEpollEvents.get(),eventNum,delay);
    if(pollNum<0)
    {
        std::cout<<"epoll_wait error! "<<errno<<std::endl;
        throw std::exception(); 
    }
    for(int i=0;i<pollNum;++i)
    {
        int sockfd=mEpollEvents[i].data.fd;
        if(sockfd==server.mListenFd)    // 判断是否是监听套接字,listenFd没有设置成ONESHOT模式
        {
           std::cout<<"new connect"<<std::endl;
           sockaddr_in addr;
           socklen_t addrLen=sizeof(addr);
           int connFd=server.accept(&addr);
           if(connFd<0)
           {
               std::cout<<"wrong connect"<<std::endl;
               continue;
           }
           if(connFd>MAX_EVENT_NUM)
           {
               std::cout<<"server busy"<<std::endl;
               continue;
           }
           //std::shared_ptr<HttpData> usrDataPtr=std::make_shared<HttpData>(addr,addrLen,connFd);
           userData[connFd]->init(addr,addrLen,connFd);
           //加入定时器
           std::shared_ptr<TimeNode> timeNodePtr=mTimer.addTimer(userData[connFd],300);
           userData[connFd]->setTimer(timeNodePtr);
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
            std::cout<<"new request!"<<std::endl;
            if(userData[sockfd]->mRequest->read(userData[sockfd]->mClientSocket->sockFd))
            {
                //TODO 将任务加入ThreadPool queue
                result.emplace_back(userData[sockfd]);
                //mThreadpool.add(std::bind(Server::doRequest(),*(userDataMap[sockfd]->));
            }
            else
            {
                std::cout<<"read false"<<std::endl;
                delFd(sockfd);
                userData[sockfd]->closeTime();
            }
        }
        else if(mEpollEvents[i].events & EPOLLOUT)
        {

            std::cout<<"new response!"<<std::endl;
            //将响应发送给用户
            if(!userData[sockfd]->write())
            {
                std::cout<<"write false!"<<std::endl;
                delFd(sockfd);
                userData[sockfd]->closeTime();
            }
        }
    }
    return result;
}
