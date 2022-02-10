#include "Socket.h"
#include <iostream>
#include <exception>
#include "Epoll.h"

ServerSocket::ServerSocket(int port=8080,std::string address=std::string())
{
    mIp=address;
    mAddr.sin_family=AF_INET;
    mAddr.sin_port=port;
    if(mIp.empty())
    {
        mAddr.sin_addr.s_addr=htonl(INADDR_ANY);
        //只有在accept之后，才能用getsockname获取绑定的ip地址
    }
    else
    {
        if(inet_pton(AF_INET,address.c_str(),&mAddr.sin_addr.s_addr)<0)
        {
            perror("point to net failed");
            throw std::exception();
        }
    }
    if((mListenFd=socket(PF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket create failed");
        throw std::exception();
    }
    setNonBlocking(mListenFd);
    //设置reuse标志，方便重启服务器
    int opt=1;
    setsockopt(mListenFd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
}

void ServerSocket::bind()
{
    if(::bind(mListenFd,(struct sockaddr*)&mAddr,sizeof(mAddr)<0))
    {
        perror("bind failed");
        throw std::exception();
    }
    return;
}

void ServerSocket::listen(int backlog)
{
    if(::listen(mListenFd,backlog)<0)
    {
        perror("listen failed");
        throw std::exception();
    }
    return;
}

int ServerSocket::accept(ClientSocket &clientSock)
{
    int fd=::accept(mListenFd,(sockaddr*)&clientSock.mAddr,&clientSock.mAddrLen);
    if(fd<0)
    {
        if(errno==EWOULDBLOCK||errno==EAGAIN)
            return 0;
        perror("accept failed");
        return fd;
    }
    clientSock.sockFd=fd;
    return fd;
}
