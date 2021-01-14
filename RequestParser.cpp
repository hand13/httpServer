
#include "RequestParser.h"
#include "Request.h"
RequestParser::RequestParser(const char * buffer,int bufferLength) {
    this->buffer = buffer;
    this->bufferLength = bufferLength;
    lookup = 0;
}
Request RequestParser::parseRequest() {
    Request req;
    req.url = "nice to meet you";
    return req;
}