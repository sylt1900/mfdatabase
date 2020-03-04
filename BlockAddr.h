#ifndef BLOCKADDR_H
#define BLOCKADDR_H
#include "DBout.h"

class BlockAddr
{
    public:
        BlockAddr(){}
        BlockAddr(int fo,int bo){fileoffset=fo;blockoffset=bo;}
        ~BlockAddr(){}
        int fileoffset=-1;
        int blockoffset=-1;
        void setoffset(int fo,int bo){fileoffset=fo;blockoffset=bo;}
        void show_addr(){
            PrintScreen("[f:b]--["+std::to_string(this->fileoffset)+":"+std::to_string(this->blockoffset)+"]\n");
        };
    private:
};

#endif // BLOCKADDR_H
