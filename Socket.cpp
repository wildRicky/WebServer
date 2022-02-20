#include "Socket.h"
#include <iostream>
#include <exception>
#include "Epoll.h"
#include "HttpRequest.h"
#include <string.h>

ServerSocket::ServerSocket(int port=8080,std::string address=std::string())
{
    bzero(&mAddr,sizeof(mAddr));
    mIp=address;
    std::cout<<" IP:port = "<<mIp<<":"<<port<<std::endl;
    mAddr.sin_family=AF_INET;
    mAddr.sin_port=htons(port);
    if(mIp.empty())
    {
        mAddr.sin_addr.s_addr=htonl(INADDR_ANY);
        //只有在accept之后，才能用getsockname获取绑定的ip地址
    }
    else
    {
        if(inet_pton(AF_INET,address.c_str(),&mAddr.sin_addr.s_addr)==0)
        {
            std::cout<<"point to net failed"<<std::endl;
            throw std::exception();
        }
    }
    if((mListenFd=socket(PF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket create failed");
        throw std::exception();
    }
    std::cout<<"Socket : "<<mListenFd<<std::endl;
    setNonBlocking(mListenFd);
    //设置reuse标志，方便重启服务器
    int opt=1;
    setsockopt(mListenFd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
}
ServerSocket::~ServerSocket()
{
    std::cout<<"server close"<<std::endl;
    ::close(mListenFd);
}
void ServerSocket::bind()
{
    std::cout<<"bind"<<std::endl;
    int ret=::bind(mListenFd,(sockaddr*)&mAddr,sizeof(mAddr));
    if(ret==0)
    {
        std::cout<<"bind success"<<std::endl;
    }else
    {
        std::cout<<"bind failed : "<<errno<<std::endl;
        throw std::exception();
    }
    return;
}

void ServerSocket::listen(int backlog)
{
    std::cout<<"listen"<<std::endl;
    int ret=::listen(mListenFd,backlog);
    if(ret==0)
    {
        std::cout<<"listen success"<<std::endl;
    }
    else
    {
        std::cout<<"listen failed : "<<errno<<std::endl;
        throw std::exception();
    }
    return;
}

int ServerSocket::accept(sockaddr_in* clientAddr)
{
    socklen_t addrLen=sizeof(clientAddr);
    int fd=::accept(mListenFd,(sockaddr*)&clientAddr,&addrLen);
    if(fd<0)
    {
        if(errno==EWOULDBLOCK||errno==EAGAIN)
            return 0;
        perror("accept failed");
        return fd;
    }
    return fd;
}

ClientSocket::~ClientSocket()
{
    ::close(sockFd);
}
