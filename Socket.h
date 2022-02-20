#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

class ClientSocket;

class ServerSocket
{
public:
    ServerSocket(int port,std::string address);
    ~ServerSocket();
    void bind();
    void listen(int);
    int accept(sockaddr_in*);
    int getListenFd()
    {
        return mListenFd;
    }
    int mListenFd;
public:
    sockaddr_in mAddr;
    std::string mIp;
};

class ClientSocket
{
public:
    ClientSocket(sockaddr_in addr,socklen_t len,int fd):mAddr(addr),mAddrLen(len),sockFd(fd){};
    ~ClientSocket();
    sockaddr_in mAddr;
    socklen_t mAddrLen;
    int sockFd;
};
