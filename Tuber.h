#ifndef TUBER_H
#define TUBER_H
#include "Const.h"
#include "Element.h"
#include "BlockAddr.h"
#include "DBout.h"

class Tuber
{
public:
    Tuber();
    Tuber(int size,int datalength,BlockAddr e_addr,Element e[MAX_ATTR]);
    Tuber(const Tuber& t);
    Tuber& operator = (const Tuber& t){
        this->datalength=t.datalength;
        this->size=t.size;
        this->pkpos=t.pkpos;
        for(int i=0;i<t.size;i++)
            this->e[i]=t.e[i];
        this->e_addr=t.e_addr;
        return *this;
    }
    ~Tuber();
    Element e[MAX_ATTR];
    int size=0;
    int pkpos=0;
    int datalength=0;
    BlockAddr e_addr;
    void set_tuber(Element e[MAX_ATTR],int size,int datalength,BlockAddr e_addr);
    void show_tuber();
    void disp_tuber(){
        for(int i=0;i<size;i++){
            PrintScreen(this->e[i].data+"\t");
        }
        PrintScreen("\n");
    };
protected:

private:
};

#endif // TUBER_H
