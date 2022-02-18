#include "Server.h"
#include "ThreadPool.h"
#include "Epoll.h"

std::string INDEX_PAGE = "<!DOCTYPE html>\n"
                    "<html>\n"
                    "<head>\n"
                    "    <title>Welcome to LC WebServer!</title>\n"
                    "    <style>\n"
                    "        body {\n"
                    "            width: 35em;\n"
                    "            margin: 0 auto;\n"
                    "            font-family: Tahoma, Verdana, Arial, sans-serif;\n"
                    "        }\n"
                    "    </style>\n"
                    "</head>\n"
                    "<body>\n"
                    "<h1>Welcome to LC WebServer!</h1>\n"
                    "<p>If you see this page, the lc webserver is successfully installed and\n"
                    "    working. </p>\n"
                    "\n"
                    "<p>For online documentation and support please refer to\n"
                    "    <a href=\"https://github.com/MarvinLe/WebServer\">LC WebServer</a>.<br/>\n"
                    "\n"
                    "<p><em>Thank you for using LC WebServer.</em></p>\n"
                    "</body>\n"
                    "</html>";
void Server::run(int maxThreadNum,int maxRequestNum)
{
    ThreadPool mPool(maxThreadNum,maxRequestNum);
    const Epoll::MAX_EVENT_NUM=maxThreadNum+1000;
    Epoll mEpoll(maxThreadNum+1000);   //输入参数为最大的fd
    int listenFd=mServerSocket.getListenFd();
    Epoll.addFd(listenFd,false); //listenFd不要设置ONESHOT
    while(true)
    {
       if(!mEpoll.poll(listenFd,maxThreadNum,600))
           break;
    }
    return;
}

void Server::doRequest(std::shared_ptr<void> arg)
{
    std::shared_ptr<HttpData> userDataPtr=static_cast<std::shared_ptr<HttpData>(arg);
    auto responsePtr=userDataPtr->mResponse;
    auto requestPtr=userDataPtr->mrequest;
    if(requestPtr->parseContent()==HTTP_CODE::GET_REQUEST)
    {
        if(mUrl.find("index.html")!=std::string::npos)
        {
            responsePtr->setStatusCode(200);
            responsePtr->setVersion(requestPtr->mHttpVersion);
            responsePtr->setMimeType(".html");
            responsePtr->setKeepAlive(true);
            responsePtr->setContentLength(sizeof(INDEX_PAGE));
            responsePtr->setBody(INDEX_PAGE);
            Epoll::modFd(HttpData::epollFd,userDataPtr->mClientSocket->sockFd,EPOLLOUT);//这里会停止接受消息，等待写入。可以保持连接的一致性。
        }
    }

}
