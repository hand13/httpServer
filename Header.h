#pragma once
#include <string>
class Header{
    public:
    Header(std::string&& key,std::string&& value);
    std::string key;
    std::string value;
};