#pragma once
#include <string>
#include <vector>
#include "Header.h"
#include <map>
class Request {
    private:
    std::string url;
    std::vector<Header> headers;
    std::map<std::string,std::string> parameters;
    std::vector<char> content;
    public:
    Request();
    static Request fromMessage(const char * buffer,int bufferLength);
    std::string getUrl() const;
    std::string getHeader(const std::string && key)const;
    std::string getPrameter(const std::string && key)const;
    std::vector<char> getContent()const;
};