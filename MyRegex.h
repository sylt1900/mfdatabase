#ifndef MYREGEX_H
#define MYREGEX_H
#include <string>
#include <regex>
static bool isname(std::string str){
    return regex_match(str,std::regex("\\w{1,20}"));
}
static bool isDigit(std::string str){
    return regex_match(str,std::regex("\\d{1,2}"));
}
static bool isNum(std::string str){
    return regex_match(str,std::regex("\\d{1,10}"));
}
static bool notchar(std::string str){
    return !regex_search(str,std::regex("[a-z]"));
}
#endif // MYREGEX_H
