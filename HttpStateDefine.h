#pragma once
enum class HTTP_METHOD
{
    GET,
    HEAD,
    POST,
    PUT,
    DELETE
}

enum class HTTP_HEAD
{
    USER_AGENT,
    ACCEPT_ENCODING,
    ACCEPT_DATETIME,
    HOST,
    CONNECTION,
    UPGRADE
}

enum class PARSE_STATE //主状态机状态
{
    PARSE_METHOD,
    PARSE_HEAD,
    PARSE_DATA
}

enum class LINE_STATE  //从状态机状态
{
    LINE_FINISH,
    LINE_MORE,
    LINE_BAD
}

enum class HTTP_CODE
{
    NO_REQUEST,
    GET_REQUEST,
    BAD_REQUEST,
    FORBIDDEN_REQUEST,
    INTERNAL_ERROR
}

