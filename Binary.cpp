#include "Binary.h"

Binary::Binary(){
    this->BinStream=NULL;
    this->StreamType=0x00;
    this->StreamLength=0x00;
}
Binary::Binary(int data){
    this->BinStream=new byte[4];
}
Binary::Binary(float data){}
Binary::Binary(std::string data){}

void Binary::setBin(int data){}
void Binary::setBin(float data){}
void Binary::setBin(std::string data){}

Binary::~Binary(){

}
