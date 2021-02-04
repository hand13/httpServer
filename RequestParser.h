#pragma once
#include <string>
#include "Request.h"
class RequestParser {
    private:
    int lookup;
    const char * buffer;
    int bufferLength;
    bool hasNext();
    std::string getNextLine();
    bool isNextEmptyLine();
    public:
    RequestParser(const char * buffer,int bufferLength);
    Request parseRequest();
};

std::vector<std::string> splitString(std::string str);