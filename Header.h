#pragma once
#include <string>
class Header{
    public:
    Header(const std::string& key,const std::string& value);
    std::string key;
    std::string value;
};