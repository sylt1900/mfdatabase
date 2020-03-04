#ifndef DATA_H
#define DATA_H
#include <string>

class Data{
public:
    short flag;
    //-1-int 0-float 1~255-char.
    virtual ~Data(){};
};

class Datai : public Data{
public:
    Datai(int i):x(i){
        flag = -1;
    };
    virtual ~Datai(){}
    int x;
};

class Dataf : public Data{
public:
    Dataf(float f):x(f){
        flag = 0;
    };
    virtual ~Dataf(){}
    float x;
};

class Datac : public Data{
public:
    Datac(std::string c):x(c){
        flag = c.length();
        if(flag==0)
            flag = 1;
    };
    virtual ~Datac(){}
    std::string x;
};

#endif // DATA_H
