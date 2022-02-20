#pragma once
#include "HttpStateDefine.h"
#include <memory>

class HttpRequest
{
private:

    LINE_STATE _parseLine();
    HTTP_CODE _parseRequestLine(const std::string &);
    HTTP_CODE _parseHeadLine(const std::string &);
    HTTP_CODE _parseDataLine(const std::string &);
    bool checkContentExsit();
    std::unique_ptr<char[]> buff;
    int startIndex;
    int readIndex;
    PARSE_STATE curParseState;
public:
    std::string mUrl;
    HTTP_METHOD mMethod; 
    std::string mVersion;
    std::string mContent;

public:
    static const int READ_BUFFER_SIZE;
    HTTP_CODE parseContent();
    HttpRequest();
    void init();
    bool read(int);
};

