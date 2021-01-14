#pragma once
class Request;
class RequestParser {
    private:
    int lookup;
    const char * buffer;
    int bufferLength;
    public:
    RequestParser(const char * buffer,int bufferLength);
    Request parseRequest();
};