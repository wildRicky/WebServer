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
    int accept(ClientSocket &);
private:
    sockaddr_in mAddr;
    int mListenFd;
    std::string mIp;
};

class ClientSocket
{
public:
    sockaddr_in mAddr;
    socklen_t mAddrLen;
    int sockFd;
};
