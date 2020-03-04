#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>
#include "DBout.h"

class Element {
public:
    Element(){}
    ~Element(){}
    //unsigned char* data;
    int type=-1;
    int datasize=0;
    std::string data;
    void set_element(int type,int datasize,std::string data);
    void show_element();
protected:

private:
};

#endif // ELEMENT_H
