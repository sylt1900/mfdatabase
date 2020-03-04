#include "RecoderManager.h"

Buffmanager bufferlist_rm;

RecoderManager::RecoderManager()
{
    //ctor
}

RecoderManager::~RecoderManager()
{
    //dtor
}
void RecoderManager::RMCREATETABLE(std::string tablename, int attrlength, Attr attrs[MAX_ATTR])
{
    if(DEBUG_OPT)
        PrintScreen("in rm tablename is "+tablename+"\n");
    Filemanager f_table(tablename+".table");
    f_table.write_(tablename);
    f_table.write_(attrlength);
    for(int i=0;i<attrlength;i++){
        f_table.write_(attrs[i].attrname);
        f_table.write_(attrs[i].attrtype);
        f_table.write_(attrs[i].attrlength);
        f_table.write_(attrs[i].isnull);
        f_table.write_(attrs[i].ispkey);
        f_table.write_(attrs[i].isunique);
    }
}

BlockAddr RecoderManager::RMstoredata(Tuber tuber, std::string tablename)
{
    Filemanager fl(tablename+".db");
    BlockAddr tuber_addr = fl.get_a_block(tuber.datalength);
    std::fstream f_link(tablename+".link",std::ios::app);
    int integer;
    float float_num;
    std::string str_rm;
    int offset=(tuber_addr.fileoffset)*MAX_BLOCK_SIZE+tuber_addr.blockoffset;

    if(DEBUG_OPT||DEBUG_RM){
        tuber_addr.show_addr();
        PrintScreen("offset="+std::to_string(offset)+"\n");
    }

    f_link <<tuber.e[tuber.pkpos].data<<" "<< tuber_addr.fileoffset<<" "<<tuber_addr.blockoffset<<std::endl;

    std::stringstream transtype;
    for(int i=0;i<tuber.size;i++){
        transtype.clear();
        transtype.str("");
        transtype << tuber.e[i].data;
        if(tuber.e[i].type==0){
            transtype >> integer;
            fl.write_data((unsigned char*)&integer,offset,tuber.e[i].datasize);
        }else if(tuber.e[i].type==1){
            transtype >> float_num;
            fl.write_data((unsigned char*)&float_num,offset,tuber.e[i].datasize);
        }else if(tuber.e[i].type==2){
            transtype >> str_rm;
            unsigned char dst_str[tuber.e[i].datasize]={0};
            for(int i=0;i<str_rm.length();i++)
                dst_str[i]=str_rm[i];
            fl.write_data(dst_str,offset,tuber.e[i].datasize);
        }
        offset+=tuber.e[i].datasize;
    }
    f_link.close();
    f_link.clear();
    return tuber_addr;

}

Tuber RecoderManager::RMreaddata(BlockAddr addr, std::string tablename, Attr attrs[MAX_ATTR],int attrlength)
{
    Filemanager f_db(tablename+".db");
    Element array_e[MAX_ATTR];
    int offset=(addr.fileoffset)*MAX_BLOCK_SIZE+addr.blockoffset;
    int old_offset=offset;
    for(int i=0;i<attrlength;i++){
        array_e[i].datasize=attrs[i].attrlength;
        array_e[i].type=attrs[i].attrtype;
        if(array_e[i].type==0){
            int integer=0;
            f_db.get_data(offset,array_e[i].datasize,(unsigned char*)&integer);
            array_e[i].data=std::to_string(integer);
        }
        if(array_e[i].type==1){
            float float_num=0.0;
            f_db.get_data(offset,array_e[i].datasize,(unsigned char*)&float_num);
            array_e[i].data=std::to_string(float_num);
        }
        if(array_e[i].type==2){
            char str_data[(array_e[i].datasize)+1]={0};
            f_db.get_data(offset,array_e[i].datasize,(unsigned char*)str_data);
            array_e[i].data=str_data;
            if(DEBUG_RM||DEBUG_OPT){
                PrintScreen("the datasize is"+std::to_string(array_e[i].datasize)+" data:");
                for(int j=0;j<array_e[i].datasize;j++)
                    PrintScreen(std::to_string((int)str_data[j])+" ");
                PrintScreen("\n");
            }
        }else{

        }
        offset+=array_e[i].datasize;

    }
    Tuber ret(attrlength,offset-old_offset,addr,array_e);
    return ret;
}


void RecoderManager::RMCREATEDB(std::string tablename)
{
    Filemanager f_db(tablename+".db");
}
void RecoderManager::RMCREATEINDEX(std::string tablename)
{
    Filemanager f_index(tablename+".index");
}

//void RecoderManager::RMCREATEBACK(std::string tablename)
//{
//    Filemanager f_back(tablename+".back");
//}
void RecoderManager::RMCREATELINK(std::string tablename)
{
    Filemanager f_back(tablename+".link");
}

void RecoderManager::RMCREATEFILE(std::string fn)
{
    Filemanager f_file(fn);
}
