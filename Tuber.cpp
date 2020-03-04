#include "Tuber.h"

Tuber::Tuber()
{
    //ctor
}
Tuber::Tuber(const Tuber& t)
{
    this->datalength=t.datalength;
    this->size=t.size;
    for(int i=0;i<t.size;i++)
        this->e[i]=t.e[i];
    this->e_addr=t.e_addr;
    this->pkpos=t.pkpos;
}

Tuber::Tuber(int size,int datalength,BlockAddr e_addr,Element e[MAX_ATTR])
{
    this->datalength=datalength;
    this->size=size;
    for(int i=0;i<size;i++)
        this->e[i]=e[i];
    this->e_addr=e_addr;
}
void Tuber::show_tuber()
{
    PrintScreen("datalength:"+std::to_string(this->datalength)+"\n");
    PrintScreen("dataSize:"+std::to_string(this->size)+"\n");
    for(int i=0;i<this->size;i++){
        this->e[i].show_element();
    }
    this->e_addr.show_addr();
}

void Tuber::set_tuber(Element e[MAX_ATTR], int size, int datalength, BlockAddr e_addr)
{
    this->datalength=datalength;
    this->size=size;
    for(int i=0;i<size;i++)
        this->e[i]=e[i];
    this->e_addr=e_addr;
}




Tuber::~Tuber()
{
    //dtor
}
