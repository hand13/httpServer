
#include "RequestParser.h"
RequestParser::RequestParser(const char * buffer,int bufferLength) {
    this->buffer = buffer;
    this->bufferLength = bufferLength;
    lookup = 0;
}
Request RequestParser::parseRequest() {
    Request req;
    if(hasNext() && !isNextEmptyLine()) {//method
        std::string title = getNextLine();
        auto m = splitString(title);
        if(m.size() >= 3) {
            req.method = m[0];
            req.url = m[1];
            req.protocol = m[2];
        }
    }
    while(hasNext() && !isNextEmptyLine()) {//header
        std::string header = getNextLine();
        auto i = header.find_first_of(':');
        auto key = header.substr(0,i);
        auto value = header.substr(i+1);
        req.headers.push_back(Header(key,value));
    }
    lookup++;
    //body
    if(hasNext()) {
        for(int h = lookup;h<bufferLength;h++) {
            req.content.push_back(buffer[h]);
        }
    }
    lookup = bufferLength;
    return req;
}
bool RequestParser::hasNext() {
    return lookup < bufferLength;
}
bool RequestParser::isNextEmptyLine() {
    return buffer[lookup] == '\n';
}
std::string RequestParser::getNextLine() {
    bool find = false;
    std::string result;
    int i = 0;
    for(i = lookup;i<bufferLength;i++) {
        if(buffer[i] == '\r' && (i+1) <bufferLength && buffer[i+1] == '\n') {
            find = true;
            break;
        }else {
            result.push_back(buffer[i]);
        }
    }
    if(find) {
        lookup = i + 2;
        return result;
    }
    return "";
}

std::vector<std::string> splitString(std::string str) {
    std::vector<std::string> result;
    std::string tmp = str;
    while(tmp.size() > 0) {
        auto t = tmp.find_first_of(' ');
        if (t != std::string::npos) {
            result.push_back(tmp.substr(0, t));
            tmp = tmp.substr(t + 1);
        }
        else {
            result.push_back(tmp);
            tmp = "";
        }
    }
    return result;
}