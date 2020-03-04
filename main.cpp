#include <iostream>
#include <stdio.h>
#include "Filemanager.h"
#include <fstream>
#include <string>
#include <sstream>
#include "Buffmanager.h"
#include "InterManager.h"
#include "Table.h"
//#include "Data.h"
using namespace std;

int main(){
    /*
    byte a=0xff;
    printf("%x\n",a);
    cout <<hex<<a;
    try{
        int a=0xffffffff;
        int *p = new int[a];
    }catch(std::bad_alloc ba){
        cout <<"fdjkfld"<<endl;
    }*/
    /*Filemanager file("test.txt");
    std::cout <<file.filename;
    std::cout <<" "<<file.filelength<<"\n";
    std::cout <<"p"<<file.p_pos<<"g"<<file.g_pos<<"\n";
    int num=1234;
    unsigned char* a = (unsigned char*)&num;

    file.write_data(a,3,4);
    unsigned char outstr[4];
    file.get_data(3,4,outstr);
    int *pint = (int*)outstr;
    std::cout <<*pint;*/
    //BuffBlock b;
    //b.show_block_status();
    InterManager intm;
    //istream infile("test_parph_words.txt");
    int ret=1;
    while(ret){
        cout <<">>>";
        intm.GetQs();

        //intm.Normolize();
        try{
            ret=intm.EXEC();
        }catch(QueryException qe){
            cout <<qe.what()<<endl;
        }catch(TableException te){
            cout <<te.what()<<endl;
        }
//        stringstream ss;
//        ss << intm.qs;
//        string tempout;
//        PrintScreen(intm.qs+"\n");
//        while(ss >> tempout){
//            cout <<tempout<<endl;
//        }
    }
//    cout <<"test table copy"<<endl;
//    Table t1;
//    Table t2;
//    string tablename = "City";
//    int attr_length = 5;
//    Attr attrs[MAX_ATTR];
//    attrs[0].setAttr("ID",0,4,1,1,0);
//    attrs[1].setAttr("Name",2,35,0,1,0);
//    attrs[2].setAttr("CountryCode",2,3,0,0,0);
//    attrs[3].setAttr("District",2,30,0,0,0);
//    attrs[4].setAttr("Population",0,4,0,0,0);
//    Element arrays[MAX_ATTR];
//    arrays[0].set_element(0,4,"10");
//    arrays[1].set_element(2,35,"test");
//    arrays[2].set_element(2,3,"jp");
//    arrays[3].set_element(2,30,"testdis");
//    arrays[4].set_element(0,4,"100");
//    vector <Tuber> tubers;
//    tubers.push_back(Tuber(attr_length,4+35+3+30+4,BlockAddr(0,0),arrays));
//    t1.set_table(tablename,attr_length,1,tubers,attrs);
//    t2=t1;
//    t2.show_table();
//    t2.tubers[0].show_tuber();
//    Filemanager filemanager("CREAPER");
//    while(true){
//        cout <<"test filemanager"<<endl;
//        int num=0;
//        cin >>num;
//        filemanager.get_a_block(num).show_addr();
//        //filemanager.get_a_block(10).show_addr();
//        //filemanager.get_a_block(4087).show_addr();
//    }


}
