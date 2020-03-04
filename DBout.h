#ifndef DBOUT_H_INCLUDED
#define DBOUT_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Const.h"



static void PrintScreen(std::string data){
    if(TO_SCREEN)
        std::cout <<data;
    if(TO_FILE){
        std::fstream outfile;
        outfile.open("outfile.outfile",std::ios::app);
        if(!outfile.is_open()){
            std::cout <<"Can not open the outfile\n";
            exit(1);
        }
        outfile <<data;
        outfile.close();

    }
    if(TO_CONNECT){
        //mysocket.sendData=data;
        //mysocket._SendMessage();
        //remove("socketMessage.socket");
        std::fstream outfile;
        outfile.open("socketMessage.socket",std::ios::app);
        if(!outfile.is_open()){
            std::cout <<"Can not open the socketfile\n";
            exit(1);
        }
        outfile <<data;
        outfile.close();
    }
}


#endif // DBOUT_H_INCLUDED
