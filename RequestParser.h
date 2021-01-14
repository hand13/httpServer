#pragma once
#include "Request.h"
class RequestParser {
    private:
    int lookup;
    const char * buffer;
    int bufferLength;
    public:
    RequestParser(const char * buffer,int bufferLength);
    Request parse();
};