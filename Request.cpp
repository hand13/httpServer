#include "Request.h"
Request::Request(){
}
std::string Request::getUrl() const{
    return url;
}
std::string Request::getHeader(const std::string & key) const{
    return "";
}
std::string Request::getPrameter(const std::string & key)const{
    return parameters.at(key);
}
std::vector<char> Request::getContent() const{
    return content;
}
std::string Request::getMethod() const{
    return method;
}