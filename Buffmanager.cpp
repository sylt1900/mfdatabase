#include "Buffmanager.h"

Buffmanager::Buffmanager()
{
    //ctor
}

Buffmanager::~Buffmanager()
{
    //dtor
}
int Buffmanager::getABufferB(){
    for(int i=0;i<MAX_BUFF_SIZE;i++)
        if(this->bufflist[i].usetime==-1){
            this->usedbuffsize+=1;
            this->usedbuffpos.push_back(i);
            return i;
        }
        return -1;
}
