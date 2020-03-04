#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <exception>
#include <string>

class TableException: public std::exception{
public:
    TableException(std::string s):text(s){}
    std::string what(){
        return text;
    };
private:
    std::string text;
};
class QueryException: public std::exception{
public:
    QueryException(std::string s):text(s){}
    std::string what(){
        return text;
    };
private:
    std::string text;
};
class MemoryException: public std::exception{
public:
    MemoryException(std::string s):text(s){}
    std::string what(){
        return text;
    };
private:
    std::string text;
};

#endif // MYEXCEPTION_H
