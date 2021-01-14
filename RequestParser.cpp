
#include "RequestParser.h"
RequestParser::RequestParser(const char * buffer,int bufferLength) {
    this->buffer = buffer;
    this->bufferLength = bufferLength;
    lookup = 0;
}
Request RequestParser::parse() {
    return Request();
}