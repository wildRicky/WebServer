#include <memory>
#include "HttpRequest.h"
#include <sys/socket.h>
#include <iostream>

const int HttpRequest::READ_BUFFER_SIZE=4096;
HttpRequest::HttpRequest():
buff(std::unique_ptr<char[]>(new char[READ_BUFFER_SIZE])){}

void HttpRequest::init()
{
    startIndex=0;
    readIndex=0;
    curParseState=PARSE_STATE::PARSE_METHOD;
}

LINE_STATE HttpRequest::_parseLine()
{
    char c;
    for(int start=startIndex;start<readIndex;++start)
    {
        c=buff[start];               //注意不能使用*(buff)[startIndex],因为*(buff)的结果应该是char*,失去了数组意义，相当于数组作形式参数传入函数中，应当直接使用重载的[]运算符。
        if(c=='\r')
        {
            if(start+1==readIndex)
                return LINE_STATE::LINE_MORE;
            else if((buff)[start+1]=='\n')
            {

                (buff)[start++]='\0';
                (buff)[start++]='\0';
                return LINE_STATE::LINE_FINISH;
            }
            return LINE_STATE::LINE_BAD;
        }else if(c=='\n')
        {
            if(start>1&&(buff)[start-1]=='\r')
            {
                (buff)[start-1]='\0';
                (buff)[start++]='\0';
                return LINE_STATE::LINE_FINISH;
            }
            return LINE_STATE::LINE_BAD;
        }
    }   
    return LINE_STATE::LINE_BAD; 
}

HTTP_CODE HttpRequest::parseContent()
{
   LINE_STATE lineState=LINE_STATE::LINE_FINISH;
   HTTP_CODE retCode=HTTP_CODE::NO_REQUEST;
   while((lineState=_parseLine())==LINE_STATE::LINE_FINISH)
   {
       std::string str=std::string(buff.get()+startIndex);
       startIndex+=str.size()+2;
       switch(curParseState)
       {
            case PARSE_STATE::PARSE_METHOD:
            {
                retCode=_parseRequestLine(str);
                if(retCode==HTTP_CODE::BAD_REQUEST)
                    return HTTP_CODE::BAD_REQUEST;
                break;
            }
            case PARSE_STATE::PARSE_HEAD:
            {
                retCode=_parseHeadLine(str);
                if(retCode==HTTP_CODE::BAD_REQUEST)
                    return HTTP_CODE::BAD_REQUEST;
                break;
            }
            case PARSE_STATE::PARSE_DATA:
            {
                retCode=_parseDataLine(str);
                if(retCode==HTTP_CODE::BAD_REQUEST)
                    return HTTP_CODE::BAD_REQUEST;
                else if(retCode==HTTP_CODE::GET_REQUEST)
                    return retCode;
            }
            default:
                return HTTP_CODE::INTERNAL_ERROR;
       }
   }
   return retCode;
}

HTTP_CODE HttpRequest::_parseRequestLine(const std::string &str)
{
    std::cout<<"begin parse Request line"<<std::endl;
    std::cout<<str<<std::endl;
    auto urlPos=str.find_first_of(" \t");
    if(urlPos==std::string::npos)
    {
        std::cout<<"urlPos not find"<<std::endl;
        return HTTP_CODE::BAD_REQUEST;
    }
    std::string method=str.substr(0,urlPos);
    if(method=="GET")
        mMethod=HTTP_METHOD::GET;
    else if(method=="HEAD")
        mMethod=HTTP_METHOD::HEAD;
    auto levelPos=str.find_first_of(" \t",urlPos+1);
    if(levelPos==std::string::npos)
    {
        std::cout<<"levelPos not find"<<std::endl;
        return HTTP_CODE::BAD_REQUEST;
    }
    mUrl=str.substr(urlPos+1,levelPos-urlPos);
    std::string level=str.substr(levelPos+1,str.size()-levelPos-1);
    if(level=="HTTP/1.0"||level=="HTTP/1.1")
        mVersion=level;
    else
        return HTTP_CODE::BAD_REQUEST;
    curParseState=PARSE_STATE::PARSE_HEAD;
    return HTTP_CODE::GET_REQUEST;
}

HTTP_CODE HttpRequest::_parseHeadLine(const std::string &str)
{
    std::cout<<"begin parse Header line"<<std::endl;
    std::cout<<str<<std::endl;
    if(str.empty())
        return HTTP_CODE::GET_REQUEST;
    auto pos=str.find_first_of(':');
    if(pos==std::string::npos)
        return  HTTP_CODE::BAD_REQUEST;
    std::string name=str.substr(0,pos);
    std::string value=str.substr(pos+1,str.size()-pos-1);
    return HTTP_CODE::NO_REQUEST;
}

HTTP_CODE HttpRequest::_parseDataLine(const std::string &str)
{
    std::cout<<"begin parse Data line"<<std::endl;
    return HTTP_CODE::NO_REQUEST;
}

bool HttpRequest::read(int sockfd)
{
    std::cout<<"begin read!"<<std::endl;
    if(readIndex>=READ_BUFFER_SIZE)
    {
        return false;
    }
    int byteRead=0;
    while(true)
    {
        byteRead=::recv(sockfd,buff.get()+readIndex,READ_BUFFER_SIZE-readIndex,0);
        if(byteRead==-1)
        {
            if(errno==EAGAIN||errno==EWOULDBLOCK)
                break;
            return false;
        }else if(byteRead==0)
            return false;
        readIndex+=byteRead;
    }
    return true;
}
