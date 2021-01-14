#pragma once
#include "Header.h"
#include <vector>
enum ResponseStatus {
    OK=200,
    BAD_REQUEST=400,
    NO_FOUND = 404,
    SERVER_ERROR=500
};
class Response {
    private:
    int protocol;
    int status;
    std::vector<Header> headers;
    std::vector<unsigned char> content;
    public:
    Response();
    void setProtocol(int protocol);
    void setStatus(ResponseStatus stauts);
    void addHeader(const Header &&header);
    void setContent(const char * buffer,int length);
    void setContent(const std::string && content);
    void toMessage(char * buffer,int bufferLength,int& length);
};