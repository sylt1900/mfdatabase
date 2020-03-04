#include "Filemanager.h"


Filemanager::Filemanager(std::string fn)
{
    if(!isexist(fn)){
        this->file_stream.open(fn,std::ios::out);
        this->file_stream.close();
        this->file_stream.clear();
    }
    this->file_stream.open(fn,std::ios::in|std::ios::out|std::ios::binary);
    //this->file_stream.open(fn,std::ios::app);
    if(DEBUG_OPT){
        if(!this->file_stream.is_open()){
            PrintScreen("Can't open file "+fn+"\n");
            this->file_stream.clear();
        }
    }
    this->filename=fn;
    this->file_stream.seekp(0,std::ios::end);
    this->filelength=this->file_stream.tellp();
    this->file_stream.seekp(0,std::ios::beg);
    this->p_pos=file_stream.tellp();
    this->g_pos=file_stream.tellg();
}

void Filemanager::write_data(unsigned char* data,int pos,int data_length){
    if(((pos+1+data_length)>this->filelength))
        return;
    this->file_stream.seekp(pos,std::ios::beg);
    //this->file_stream <<data;
    this->file_stream.write((char*)data,data_length);
    this->p_pos=file_stream.tellp();
    this->g_pos=file_stream.tellg();
}
void Filemanager::get_data(int startpos,int length,unsigned char* data){
    if(startpos>this->filelength)
        return;
    this->file_stream.seekg(startpos,std::ios::beg);
    this->file_stream.read((char*)data,length);

    this->p_pos=file_stream.tellp();
    this->g_pos=file_stream.tellg();
}

void Filemanager::open_file(std::string fn){
    this->file_stream.close();
    this->file_stream.clear();
    this->file_stream.open(fn,std::ios::in|std::ios::out|std::ios::binary);
    this->filename=fn;
    this->file_stream.seekp(0,std::ios::end);
    this->filelength=this->file_stream.tellp();
    this->file_stream.seekp(0,std::ios::beg);
    this->p_pos=file_stream.tellp();
    this->g_pos=file_stream.tellg();
}
BlockAddr Filemanager::get_a_block(int length){
    int offset=-1;
    int b_offset=-1;
    BlockAddr ret(-1,-1);
    if(length>4088||length<=0)
        return ret;
    if(this->filelength==0){
        offset=0;
        int isuse=4088-length;
        unsigned char data[MAX_BLOCK_SIZE]={0};
        this->file_stream.seekp(0,std::ios::beg);
        this->file_stream.write((char*)data,MAX_BLOCK_SIZE);
        this->file_stream.seekp(0,std::ios::beg);
        this->file_stream.write((char*)&isuse,4);
        if(DEBUG_OPT_FM||DEBUG_OPT){
            int inileng=0;
            this->file_stream.seekg(0,std::ios::beg);
            this->file_stream.read((char*)&inileng,4);
            PrintScreen("left value="+std::to_string(inileng)+"\n");
        }

        b_offset=8;
        this->filelength=MAX_BLOCK_SIZE;
    }
    else{
        int i=0;
        //block的第一个节=1block被使用
        //标志占用8字节
        //4096-8=4088;
        for(;i<((this->filelength)/MAX_BLOCK_SIZE);i++){
            int pos=i*MAX_BLOCK_SIZE;
            this->file_stream.seekg(pos,std::ios::beg);
            int isuse=0;
            this->file_stream.read((char*)&isuse,4);
            //
            if(isuse>=length)
            {
                offset=i;
                int length_=isuse-length;
                this->file_stream.seekp(pos,std::ios::beg);
                this->file_stream.write((char*)&length_,4);
                this->file_stream.seekp(pos,std::ios::beg);
                this->file_stream.write((char*)&length_,4);

                if(DEBUG_OPT_FM||DEBUG_OPT){
                    int inileng=0;
                    this->file_stream.seekg(pos,std::ios::beg);
                    this->file_stream.read((char*)&inileng,4);
                    PrintScreen("left value="+std::to_string(inileng)+"\n");
                }

                b_offset=4096-isuse;
                break;
            }
        }
        if(i==(((this->filelength)/MAX_BLOCK_SIZE))){
            offset=i;
            int isuse=4088-length;
            unsigned char data[MAX_BLOCK_SIZE]={0};
            this->file_stream.seekp(0,std::ios::end);
            this->file_stream.write((char*)data,MAX_BLOCK_SIZE);
            this->file_stream.seekp(i*MAX_BLOCK_SIZE,std::ios::beg);
            this->file_stream.write((char*)&isuse,4);
            b_offset=8;
            this->filelength+=MAX_BLOCK_SIZE;
            if(DEBUG_OPT_FM||DEBUG_OPT){
                int inileng=0;
                this->file_stream.seekg(i*MAX_BLOCK_SIZE,std::ios::beg);
                this->file_stream.read((char*)&inileng,4);
                PrintScreen("left value="+std::to_string(inileng)+"\n");
            }
        }

    }
    ret.setoffset(offset,b_offset);
    return ret;
}

void Filemanager::write_(std::string str)
{
    this->file_stream.seekp(0,std::ios::end);
    this->file_stream << str <<std::endl;
    this->file_stream.seekp(0,std::ios::beg);
    this->file_stream.seekg(0,std::ios::beg);
    this->p_pos=this->file_stream.tellp();
    this->g_pos-this->file_stream.tellg();
}

void Filemanager::write_(int integer)
{
    this->file_stream.seekp(0,std::ios::end);
    this->file_stream << integer <<std::endl;
    this->file_stream.seekp(0,std::ios::beg);
    this->file_stream.seekg(0,std::ios::beg);
    this->p_pos=this->file_stream.tellp();
    this->g_pos-this->file_stream.tellg();
}

void Filemanager::write_(bool boolean)
{
    this->file_stream.seekp(0,std::ios::end);
    this->file_stream << boolean <<std::endl;
    this->file_stream.seekp(0,std::ios::beg);
    this->file_stream.seekg(0,std::ios::beg);
    this->p_pos=this->file_stream.tellp();
    this->g_pos-this->file_stream.tellg();
}


Filemanager::~Filemanager()
{
    this->file_stream.close();
    filename="";
    filelength=0;
}
