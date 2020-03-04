#ifndef BUFFMANAGER_H
#define BUFFMANAGER_H

#include "Filemanager.h"
#include <string>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include "Const.h"
#include <vector>
#include "BlockAddr.h"
class BuffBlock
{
public:
    std::string filename="";
    int offset=-1;
    bool ischange=false;
    long long usetime=-1;
    unsigned char data[MAX_BLOCK_SIZE]={0};
    BuffBlock(){}
    BuffBlock(std::string fn){
        this->filename=fn;
        //Filemanager file_init(fn);
        //this->offset=file_init.get_a_block().blockoffset;
    }
    void show_block_status(){
        std::cout <<"[ "<<this->usetime<<" ]\nfilename="<<filename<<"\noffset="<<offset<<"\nischange="<<ischange<<"\ndata=";/**/
        for (int i=0;i<10;i++)
            printf("%x ",this->data[i]);
        std::cout <<"\n";

    }
    void set_all_data(unsigned char indata[MAX_BLOCK_SIZE]){
        for(int i=0;i<MAX_BLOCK_SIZE;i++)
            this->data[i]=indata[i];
        ischange=true;
    }
    void set_pos_data(unsigned char* indata,int length,int pos){
        if(pos+length>MAX_BLOCK_SIZE)
            return;
        for(int i=pos;i<pos+length;i++){
            this->data[i]=indata[i-pos];
        }
        ischange=true;
    }
    void get_all_data(unsigned char outdata[MAX_BLOCK_SIZE]){
        for(int i=0;i<MAX_BLOCK_SIZE;i++)
            outdata[i]=this->data[i];
    }
    void get_pos_gata(unsigned char* outdata,int length,int pos){
        if(pos+length>MAX_BLOCK_SIZE)
            return;
        for(int i=pos;i<pos+length;i++){
            outdata[i-pos]=this->data[i];
        }
    }
    void flashback(){
        if(this->ischange){
            Filemanager f_back(this->filename);
            f_back.write_data(this->data,(this->offset)*MAX_BLOCK_SIZE,MAX_BLOCK_SIZE);
        }
    }
    void refbuff(){
        Filemanager f_read(this->filename);
        f_read.get_data((this->offset)*MAX_BLOCK_SIZE,MAX_BLOCK_SIZE,this->data);
    }
};


class Buffmanager
{
public:
    BuffBlock bufflist[MAX_BUFF_SIZE];
    int getABufferB();
    int usedbuffsize=0;
    std::vector<int> usedbuffpos;

    Buffmanager();
    ~Buffmanager();
private:
};

#endif // BUFFMANAGER_H
