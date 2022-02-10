#pragma once

#include <memory>

class TimeNode;
class HttpRequest;
class ClientSocket;

class HttpData
{
public:
    int msockfd;
    std::shared_ptr<HttpRequest> mRequest;
    std::shared_ptr<ClientSocket> mClientSocket;
private:
    std::weak_ptr<TimeNode> mtimer;

};
