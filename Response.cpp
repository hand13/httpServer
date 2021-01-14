#include "Response.h"
Response::Response() {
    protocol = 1;
    status = OK;
}
void Response::setProtocol(int protocol) {
    this->protocol = protocol;
}
void Response::setStatus(ResponseStatus status) {
    this->status = status;
}
void Response::addHeader(const Header && header) {
    headers.push_back(header);
}
void Response::setContent(const char * buffer,int length) {
    for(int i =0;i<length;i++) {
        content.push_back(buffer[i]);
    }
    addHeader(Header("Content-Length",std::to_string(length)));
}
void Response::setContent(const std::string && content) {
    setContent(content.c_str(),content.size());
}
void Response::toMessage(char * buffer,int bufferLength,int & length) {
    std::string msg;
    msg += "HTTP/1.1 " + std::to_string(status) + " ";
    if(status == OK) {
        msg += "OK";
    }
    msg += "\r\n";
    for(Header & header:headers) {
        msg += header.key + ":" + header.value + "\r\n";
    }
    msg += "\n";
    int al = msg.size() + content.size();
    if(al > bufferLength) {
    }
    std::memcpy(buffer,msg.c_str(),msg.size());
    std::memcpy(buffer + msg.size(),content.data(),content.size());
    length = al;
}