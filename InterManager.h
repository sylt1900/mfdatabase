#ifndef INTERMANAGER_H
#define INTERMANAGER_H
#include "MyException.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "DBout.h"
#include "MyRegex.h"
#include "Attr.h"
#include "RecoderManager.h"
#include "Table.h"

const std::string TYPETOKEN[]= {"int","float","char"};

class InterManager {
public:
    std::string qs;//query string
    std::stringstream pop_string_to;
public:
    ~InterManager() {
        clearSStream();
    }
    void clearSStream() {
        pop_string_to.clear();
        pop_string_to.str("");
    }
    void GetQs();
    void Normolize();
    int GOGOGO(int pos);
    int EXEC();
    int isTYPETOKEN(std::string str) {
        int ret=-1;
        for(int i=0; i<3; i++)
            if(str.compare(TYPETOKEN[i])==0){
                ret=i;
                break;
            }
        return ret;
    }
    void EXEC_CREATE();
    void EXEC_CREATE_TABLE();
    void EXEC_SELECT();
    void EXEC_DROP();
    void EXEC_DROP_TABLE();
    void EXEC_DROP_INDEX();
    void EXEC_CREATE_INDEX();
    void EXEC_INSERT();
    void EXEC_DELETE();
    void EXEC_SHOW();
    void EXEC_EXIT();
    void EXEC_FILE();



    /*    void interwhere(int& pos1, std::vector<int> &attrwhere, std::vector<where> &w, Attribute A,
                   Table* t);




        //Normolize the inputting string
        int SocketGetQS(DBSocket& mysocket);*/
};

#endif // INTERMANAGER_H
