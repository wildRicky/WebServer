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
    std::unique_ptr<char[]> buff;
    int startIndex;
    int readIndex;
    PARSE_STATE curParseState;
public:
    HTTP_CODE parseContent();
    HttpRequest():curParseState(PARSE_STATE::PARSE_METHOD){};
};

