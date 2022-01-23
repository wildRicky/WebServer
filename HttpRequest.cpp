#pragma once
#include <unique_ptr>
#include "HttpRequest.h"

LINE_STATE HttpRequest::_parseLine()
{
    char c;
    for(;startIndex<readIndex;++startIndex)
    {
        c=(*buff)[startIndex];
        if(c=='\r')
        {
            if(startIndex+1=readIndex)
                return LINE_STATE::LINE_MORE;
            else if((*buff)[startIndex+1]=='\n')
            {

                (*buff)[startIndex++]='\0';
                (*buff)[startIndex++]='\0';
                return LINE_STATE::LINE_FINISH;
            }
            return LINE_STATE::LINE_BAD;
        }else if(c=='\n')
        {
            if(startIndex>1&&(*buff)[startIndex-1]=='\r')
            {
                (*buff)[startIndex-1]=='\0';
                (*buff)[startIndex++]=='\0';
                return LINE_STATE::LINE_FINISH;
            }
            return LINE_STATE::LINE_BAD;
        }
    }   
    return LINE_STATE::LINE_FINISH; 
}

HTTP_CODE HttpRequest::parseContent()
{
   LINE_STATE lineState=LINE_STATE::LINE_FINISH;
   HTTP_CODE retCode=HTTP_CODE::NO_REQUEST;
   while(lineState=parseLine(buff,startIndex,curIndex))
   {
       string str=string((*buff)+startLine);
       startLine=readIndex;
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
                if(retCode==HTTP_CODE::BAD_REQUEST)\
                    return HTTP_CODE::BAD_REQUEST;
                break;
            }
            case PARSE_STATE::PARSE_DATA:
            {
                retCode=_parseDataLine(str);
                if(retCode==HTTP_CODE::BAD_REQEST)
                    return HTTP_CODE::BAD_REQUEST;
                else if(retCode==HTTP_CODE::GET_REQUEST)
                    return HTTP_CODE::GET_REQUEST;
                break;
            }
            default:
                return HTTP_CODE::INTERNAL_ERROR;
       }
   }
}

HTTP_CODE HttpRequest::_parseRequestLine(const std::string &str)
{
    auto urlPos=str.find_first_of(" \t");
    if(urlPos==std::string::npos)
        return HTTP_CODE::BAD_REQUEST;
    std::string method=str.substr(0,urlPos);
    auto levelPos=str.find_first_of(" \t",urlPos+1);
    if(levelPos==std::string::npos)
        return HTTP_CODE::BAD_REQUEST;
    std::string url=str.substr(urlPos+1,levelPos-urlPos);
    std::string level=str.substr(levelPos+1,str.size()-levelPos-1);
    curParseState=PARSE_STATE::PARSE_HEAD;
    return HTTP_CODE::NO_REQUEST;
}

HTTP_CODE HttpRequest::_parseHeadLine(const std::string &str)
{
    auto pos=find_first_of(':');
    if(pos==std::string::npos)
        return  HTTP_CODE::BAD_REQUEST;
    string name=str.substr(0,pos);
    string value=str.substr(pos+1,str.size()-pos-1);
    return HTTP_CODE::NO_REQUEST;
}

HTTP_CODE HttpRequest::_parseDataLine(const std::string &str)
{
    return HTTP_CODE::NO_REQUEST;
}
