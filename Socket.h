#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

class ClientSocket;

class ServerSocket
{
public:
    ServerSocket(int port,std::string address);
    void bind();
    void listen(int);
    void close();
    int accept(sockaddr_in &);
    int getListenFd()
    {
        return mListenFd;
    }
private:
    sockaddr_in mAddr;
    int mListenFd;
    std::string mIp;
};

class ClientSocket
{
public:
    ClientSocket(sockaddr_in addr,socklen_t len,int fd):mAddr(addr),mAddrLen(len),sockFd(fd){};
    sockaddr_in mAddr;
    socklen_t mAddrLen;
    int sockFd;
};
