#include "HttpResponse.h"
#include <string.h>
std::unordered_map<std::string, std::string> MimeMap = {
        {".html", "text/html"},
        {".xml", "text/xml"},
        {".xhtml", "application/xhtml+xml"},
        {".txt", "text/plain"},
        {".rtf", "application/rtf"},
        {".pdf", "application/pdf"},
        {".word", "application/msword"},
        {".png", "image/png"},
        {".gif", "image/gif"},
        {".jpg", "image/jpeg"},
        {".jpeg", "image/jpeg"},
        {".au", "audio/basic"},
        {".mpeg", "video/mpeg"},
        {".mpg", "video/mpeg"},
        {".avi", "video/x-msvideo"},
        {".gz", "application/x-gzip"},
        {".tar", "application/x-tar"},
        {".css", "text/css"},
        {"", "text/plain"},
        {"default","text/plain"}
};
void HttpResponse::setMimeType(std::string str)
{
    mMimeType=MimeMap[str];
}
std::string HttpResponse::setResponse()
{
    std::string result=mHttpVersin+" "+std::to_string(mStatusCode)+" "+statusCodeMap[mStatusCode]+"\r\n";
    //sprintf(buff,"%s %d %s\r\n",mHttpVersion.c_str(),mStatusCode,statusCodeMap[mStatusCode].c_str());
    for(auto ite:headerMap)
    {
        result+=ite.first+": "+ite.second+"\r\n";
        //strcat(buff,head.c_str());        
    }
    result.append("Content-Type: "+mMimeType+"\r\n");
    //std::string tmp="Content-Type: "+mMimeType+"\r\n";
    //strcat(buff,tmp.c_str());
    result.append("Content-Length: "+std::to_string(mContentLength)+"\r\n");
   // tmp="Content-Length: "+std::to_string(mContentLength)+"\r\n";
   // strcat(buff,tmp.c_str());
    if(mKeepAlive)
    {
        result.append("Connection: keep-alive\r\n");
        //tmp="Connection: keep-alive\r\n";
    }else
    {
        result.append("Connection: close\r\n");
        //tmp="Connection: close\r\n";
    }
   // strcat(buff,tmp.c_str());
   // tmp="\r\n";
    result.append("\r\n");
    //strcat(buff,tmp.c_str());
    //strcat(buff,mBody);
    return result;
}
