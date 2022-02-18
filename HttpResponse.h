#pragma once

#include <unordered_map>


class HttpResponse
{
public:
    void setStatusCode(int c)
    {
        mStatusCode=c;
    };


    void setVersion(std::string v)
    {
        mHttpVersion=v;
    };

    void setKeepAlive(bool k)
    {
        mKeepAlive=k;
    };

    void setContentLength(int l)
    {
        mContentLength=l;
    };
    void setBody(std::string b)
    {
        mBody=std::move(b);
    }
    //void setBody(char *b)
    //{
      //  mBody=b;      //简单交换指针，注意指针的有效性
    //};

    void addHeader(std::string key,std::string value)
    {
        headerMap[key]=value;
    };

    std::string setResponse();
    void setMimeType(std::string);
private:
    std::unordered_map<int,std::string> statusCodeMap={
        {200,"OK"},
        {403,"Forbidden"},
        {404,"Not Found"}
    };
    std::unordered_map<std::string,std::string> headerMap;
public:
    int mStatusCode;
    std::string mHttpVersion;
    std::string mMimeType;
    bool mKeepAlive;
    int mContentLength;
    std::string mBody;
};
