#include "Server.h"
#include "ThreadPool.h"
#include "Epoll.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include <iostream>
std::string INDEX_PAGE = "<!DOCTYPE html>\n<html>\n<head>\n<title>Welcome to LC WebServer!</title>\n<style>\nbody {\nwidth: 35em;\nmargin: 0 auto;\nfont-family: Tahoma, Verdana, Arial, sans-serif;\n}\n</style>\n</head>\n<body>\n<h1>Welcome to LC WebServer!</h1>\n<p>If you see this page, the lc webserver is successfully installed and\nworking. </p>\n\n<p>For online documentation and support please refer to\n<a href=\"https://github.com/MarvinLe/WebServer\">LC WebServer</a>.<br/>\n\n<p><em>Thank you for using LC WebServer.</em></p>\n</body>\n</html>";
void Server::run(int maxThreadNum,int maxRequestNum)
{
    //注意一定是引用，因为线程池是单例模式，没有拷贝构造函数。如果不是单例模式，拷贝会导致semaphore和mutex和自线程不贡献
    ThreadPool &mPool=ThreadPool::getInstance(maxThreadNum,maxRequestNum);
    Epoll::MAX_EVENT_NUM=maxThreadNum+1000;
    Epoll mEpoll(maxThreadNum+1000);   //输入参数为最大的fd
    int listenFd=mServerSocket.getListenFd();
    mEpoll.addFd(listenFd,false); //listenFd不要设置ONESHOT
    ThreadTask task;
    task.process=std::bind(&Server::doRequest,this,std::placeholders::_1);
    while(true)
    {
        auto ret=mEpoll.poll(mServerSocket,maxThreadNum,-1);
        for(auto c:ret)
        {
            task.data=c;
            mPool.add(std::make_shared<ThreadTask>(task));
        }
    }
    return;
}

void Server::doRequest(std::shared_ptr<void> arg)
{
    std::cout<<"begin doRequest"<<std::endl;
    std::shared_ptr<HttpData> userDataPtr=std::static_pointer_cast<HttpData>(arg);         //shared_ptr使用专用的shared_pointer_cast进行转换
    auto responsePtr=userDataPtr->mResponse;
    auto requestPtr=userDataPtr->mRequest;
    if(requestPtr->parseContent()==HTTP_CODE::GET_REQUEST)
    {
        std::cout<<"get valid request"<<std::endl;
        if(requestPtr->mUrl.find("index.html")!=std::string::npos)
        {
            std::cout<<"request is index.html"<<std::endl;
            responsePtr->setStatusCode(200);
            responsePtr->setVersion(requestPtr->mVersion);
            responsePtr->setMimeType(".html");
            responsePtr->setKeepAlive(true);
            responsePtr->setContentLength(sizeof(INDEX_PAGE));
            responsePtr->setBody(INDEX_PAGE);
            std::cout<<"response set done"<<std::endl;
            Epoll::modFd(HttpData::epollFd,userDataPtr->mClientSocket->sockFd,EPOLLOUT);//这里会停止接受消息，等待写入。可以保持连接的一致性。
        }
    }
}
