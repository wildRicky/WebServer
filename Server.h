#pragma once
#include "Socket.h"
#include <memory>
class Server
{
public:
    explicit Server(int port=8080,std::string ip="127.0.0.1"):
    mServerSocket(port,ip)
    {
        mServerSocket.bind();
        mServerSocket.listen(20);
    }

    void run(int,int);
    void doRequest(std::shared_ptr<void> arg);
private:
    ServerSocket mServerSocket;  
};
