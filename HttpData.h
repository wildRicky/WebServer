#pragma once

#include <memory>
#include <sys/socket.h>
#include <netinet/in.h>
#include "HttpResponse.h"
class TimeNode;
class HttpRequest;
class ClientSocket;
class HttpResponse;
class HttpData
{
public:
    //int mSockfd;
    HttpData():mRequest(std::make_shared<HttpRequest>()),mResponse(std::make_shared<HttpResponse>()){};

    std::shared_ptr<HttpRequest> mRequest;
    std::shared_ptr<ClientSocket> mClientSocket;
    std::shared_ptr<HttpResponse> mResponse;
    static int epollFd;

    void init(sockaddr_in addr,socklen_t len,int connFd);
    void setTimer(std::shared_ptr<TimeNode>);
    void closeTime();
    bool write();
private:
    std::weak_ptr<TimeNode> mTimer;
};
