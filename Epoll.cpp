#include <Epoll.h>
#include <unistd.h>
#include <iostream>
#include <exception>

const int Epoll::MAX_EVENT_NUM=10000;

int setNonBlocking(int fd)
{
    int oldOption=fcntl(fd,F_GETFL);
    int newOption=oldOption|O_NONBLOCK;
    fcntl(fd,F_SETFL,newOption);
    return oldOption;
}

void Epoll::addFd(int fd)
{
    epoll_event event;
    event.events=EPOLLIN|EPOLLET|EPOLLONESHOT;
    event.data.fd=fd;
    epoll_ctl(mEpollFd,EPOLL_CTL_ADD,fd,&event);
    setNonBlocking(fd);
    return;
}

void Epoll::delFd(int fd)
{
    epoll_ctl(mEpollFd,EPOLL_CTL_DEL,fd,0);
    close(fd);
    return;
}

void Epoll::poll(int listenFd,int eventNum,int delay)
{
    int pollNum=epoll_wait(mEpollFd,mEpollEvents.get(),eventNum,delay);
    if(pollNum<0)
    {
        std::cout<<"epoll_wait error!"<<std::endl;
        throw std::exception(); 
    }
    for(int i=0;i<pollNum;++i)
    {
        int sockfd=mEpollEvents[i].data.fd;
        if(sockfd==listenFd)    //TODO 判断是否是监听套接字
        {
            
        }
        else if(mEpollEvents[i].events & (EPOLLRDHUP|EPOLLHUP|EPOLLERR))
        {
            //TODO 关闭连接
        }
        else if(mEpollEvents[i].events & EPOLLIN)
        {
            if(userData[sockfd].mRequest->read())
            {
                //TODO 将任务加入ThreadPool queue
                mThreadpool.add(std::bind(userData[sockfd].mRequesti->parseContent(),userData[sockfd]));
            }
            else
            {
                //TODO 断开链接
            }
        }
        else if(mEpollEvents[i].events & EPOLLOUT)
        {
            //将响应发送给用户
            if(!userData[sockfd].write())
            {
                //TODO 关闭连接
            }
        }
    }
    //TODO 清理服务器
}
