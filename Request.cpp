#include "Request.h"
#include "RequestParser.h"
Request::Request(){
}
Request Request::fromMessage(const char * buffer,int length) {
    RequestParser parser(buffer,length);
    return parser.parseRequest();
}
std::string Request::getUrl() const{
    return url;
}
std::string Request::getHeader(const std::string && key) const{
    return "";
}
std::string Request::getPrameter(const std::string && key)const{
    return parameters.at(key);
}
std::vector<char> Request::getContent() const{
    return content;
}