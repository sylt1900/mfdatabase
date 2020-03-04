#include "InterManager.h"
void InterManager::GetQs(){
    std::string temp;
    qs = "";
    do{
        getline(std::cin,temp);
        qs = qs + " ";
        qs = qs + temp;
    }while(qs[qs.length()-1]!=';');
    this->clearSStream();
    Normolize();
    pop_string_to << qs;
}

void InterManager::Normolize(){
    int pos;

    for(pos=0;pos<qs.length();pos++){
        if(qs[pos]=='<' || qs[pos]=='>' || qs[pos]=='=' || qs[pos]=='(' ||qs[pos]==')' ||
           qs[pos]==';' || qs[pos]==',' || qs[pos]=='*')
        {
            if(qs[pos-1]!=' ')
            {
                qs.insert(pos, " ");
                pos++;
            }

            if(qs[pos+1]!=' ')
            {
                qs.insert(pos+1, " ");
                pos++;
            }

        }
    }
    //cout << qs;
    int flag = 0;
    std::string::iterator it;
    for(it=qs.begin();it<qs.end();it++){
        if(flag==0 && (*it==' ' || *it=='\t'))
        {
            flag = 1;
            continue;
        }
        if(flag==1 && (*it==' ' || *it=='\t')){
            qs.erase(it);
            if(it!=qs.begin())
                it--;
            continue;
        }
        if(*it!=' ' && *it!='\t'){
            flag = 0;
            continue;
        }
    }

    if(qs[0]==' ')
        qs.erase(qs.begin());
    if(qs[qs.length()-1]==' ')
        qs.erase(--qs.end());

    //cout << qs;
}

int InterManager::GOGOGO(int pos){
    int pos1 = pos;
    while(pos1<qs.length() && qs[pos1]!=' ')
        pos1++;
    if(pos1==qs.length()||pos1==pos)
        throw QueryException("ERROR: invalid query format!");
    return pos1;
}

int InterManager::EXEC(){
    std::string token;
    pop_string_to >> token;
    if(DEBUG_OPT){
        PrintScreen("into Exec the token= "+token+"\n");
    }
    if(token.compare("select")==0){
        EXEC_SELECT();
        PrintScreen("Interpreter: successful select!\n");
        return 1;
    }
    else if(token.compare("drop")==0){
        EXEC_DROP();
        PrintScreen("Interpreter: successful drop!\n");
        return 1;
    }
    else if(token.compare("insert")==0){
        EXEC_INSERT();
        PrintScreen("Interpreter: successful insert!\n");
        return 1;
    }
    else if(token.compare("create")==0){
        EXEC_CREATE();
        PrintScreen("Interpreter: successful create!\n");

        return 1;
    }
    else if(token.compare("delete")==0){
        EXEC_DELETE();
        PrintScreen("Interpreter: successful delete!\n");
        return 1;
    }
    else if(qs.substr(0,10)=="show table"){
        EXEC_SHOW();
        return 1;
    }
    else if(token.compare("exit")==0){
        EXEC_EXIT();
        return 0;
    }
    else if(token.compare("execfile:")==0){
        EXEC_FILE();
        return 1;
    }
    else
        throw QueryException("ERROR: invalid query format!");
}


void InterManager::EXEC_CREATE(){
    std::string Token;
    pop_string_to >> Token;
    if(DEBUG_OPT)
        PrintScreen("into EXEC_CREATE token is "+Token+"\n");
    if(Token.compare("table")==0)
        EXEC_CREATE_TABLE();
    else if(Token.compare("index")==0)
        EXEC_CREATE_INDEX();
    else
        throw QueryException("ERROR: invalid query format!");
}
void InterManager::EXEC_CREATE_TABLE(){
    //std::cout <<"create table\n";
    std::string Token,tablename;
    Attr attrs_[MAX_ATTR];
    int attrs_length=0;
    pop_string_to >> Token;
    if(!isname(Token))
        throw QueryException("ERROR: invalid tablename format!");
    tablename = Token;
    pop_string_to >> Token;
    if(Token.compare("(")!=0)
        throw QueryException("ERROR: invalid query format, except a '(' after table name!");
    while(true){
        pop_string_to >> Token;
        if(Token.compare("primary")==0){
            pop_string_to >> Token;
            if(Token.compare("key")!=0)
                throw QueryException("ERROR: invalid query format, except 'key' after 'primary'!");
            pop_string_to >> Token;
            if(Token.compare("(")!=0)
                throw QueryException("ERROR: invalid query format, except '(' after 'primary key'!");
            pop_string_to >> Token;
            int isexistkey=0;
            for(int i=0;i<attrs_length;i++){
                if(Token.compare(attrs_[i].attrname)==0){
                    attrs_[i].isnull=false;
                    attrs_[i].isunique=true;
                    attrs_[i].ispkey=true;
                    isexistkey=1;
                }
            }
            if(isexistkey==0)
                throw QueryException("ERROR: invalid query format, primary key is not exist in table!");
            pop_string_to >> Token;
            if(Token.compare(")")!=0)
                throw QueryException("ERROR: invalid query format, except a ')' after primary key definition!");
            pop_string_to >> Token;
            if(Token.compare(")")!=0)
                throw QueryException("ERROR: invalid query format, except a ')' as the end of create statement!");
            pop_string_to >> Token;
            if(Token.compare(";")!=0)
                throw QueryException("ERROR: invalid query format, except a ';' as the end of create statement!");
            break;
        }
        if(!isname(Token))
            throw QueryException("ERROR: invalid attrname format!");
        attrs_[attrs_length].attrname=Token;
        pop_string_to >> Token;
        attrs_[attrs_length].attrtype=isTYPETOKEN(Token);
        if(isTYPETOKEN(Token)==-1)
            throw QueryException("ERROR: invalid query format, except int,float or char as data type!");
        else if(isTYPETOKEN(Token)==0||isTYPETOKEN(Token)==1){
            attrs_[attrs_length].attrlength=4;
        }else if(isTYPETOKEN(Token)==2){
            pop_string_to >> Token;
            if(Token.compare("(")!=0)
                throw QueryException("ERROR: invalid query format, except a '(' before define char length!");
            pop_string_to >> Token;
            if(!isDigit(Token))
                throw QueryException("ERROR: invalid query format, except a number as char length!");
            attrs_[attrs_length].attrlength=atoi(Token.c_str());
            if(attrs_[attrs_length].attrlength==0)
                throw QueryException("ERROR: invalid query format, the length of char is 0!");
            pop_string_to >> Token;
            if(Token.compare(")")!=0)
                throw QueryException("ERROR: invalid query format, except a ')' after char length!");
        }
        while(pop_string_to >> Token){
            if(Token.compare(";")==0)
                throw QueryException("ERROR: invalid query format, except ',' after data type!");
            if(Token.compare(",")==0)
                break;
            if(Token.compare("unique")==0){
                attrs_[attrs_length].isunique=true;
            }else if(Token.compare("null")==0){
                attrs_[attrs_length].isnull=true;
            }else{
                throw QueryException("ERROR: invalid query format, except 'null' or 'unique' to limit keyvalue!");
            }
        }

        attrs_length++;
    }
    if(isexist(tablename+".table"))
        throw TableException("ERROR: the table "+tablename+" already exits!");
    RecoderManager rm;
    rm.RMCREATETABLE(tablename,attrs_length,attrs_);
    rm.RMCREATEDB(tablename);
    rm.RMCREATEINDEX(tablename);
    rm.RMCREATELINK(tablename);
    if(DEBUG_OPT){
        std::cout <<"[tablename:"<<tablename<<"]\n";
        std::cout <<"attrsize:"<<attrs_length<<"\n";
        for(int i=0;i<attrs_length;i++){
            attrs_[i].show_attr();
        }

    }

}
void InterManager::EXEC_SELECT(){
    //std::cout <<"select\n";

    std::string TableName, Token;
    pop_string_to >> Token;
    if(Token.compare("*")==0){

    }else{
        if(isname(Token)){

        }else{

        }
    }
    pop_string_to >> Token;
    if(Token.compare("from")!=0)
        throw QueryException("ERROR: invalid query format, except 'from' before TableName!");
    pop_string_to >> Token;
    if(!isname(Token))
        throw QueryException("ERROR: invalid query format, the TableName is wrong!");
    TableName=Token;
    if(!isexist(TableName+".table"))
        throw TableException("ERROR: the table "+TableName+" is not exists");
    pop_string_to >> Token;
    Table t(TableName);
    if(Token.compare("where")==0){

    }else{
        if(Token.compare(";")==0){
            RecoderManager rm;
            std::ifstream f_link(TableName+".link");
            std::string temp_str;
            std::stringstream cut_str;
            std::string pvalue;
            int fileoffset;
            int blockoffset;
            Tuber tuber;
            std::vector<Tuber> tubers;
            while(getline(f_link,temp_str)){
                cut_str.clear();
                cut_str.str("");
                cut_str << temp_str;
                cut_str >> pvalue;
                cut_str >> fileoffset;
                cut_str >> blockoffset;
                tuber=rm.RMreaddata(BlockAddr(fileoffset,blockoffset),TableName,t.attrs,t.attr_length);
                tubers.push_back(tuber);
            }
            for(int i=0;i<tubers.size();i++)
                tubers[i].disp_tuber();
            f_link.close();
            f_link.clear();
        }else{
            throw QueryException("ERROR: invalid query format, except 'where' or ;!");
        }
    }


}
void InterManager::EXEC_DROP(){
    //std::cout <<"drop\n";
    std::string Token;
    pop_string_to >> Token;
    if(Token.compare("table")==0)
        EXEC_DROP_TABLE();
    else if(Token.compare("index")==0)
        EXEC_DROP_INDEX();
    else
        throw QueryException("ERROR: invalid query format, except 'table' or 'index' after 'drop'!");
}
void InterManager::EXEC_DROP_TABLE()
{
    std::string TableName;
    pop_string_to >> TableName;
    if(!isname(TableName))
        throw QueryException("ERROR: invalid tablename format!");
    if(!isexist(TableName+".table"))
        throw TableException("ERROR: the table "+TableName+" is not exists");
    rmfile(TableName+".table");
    rmfile(TableName+".db");
    rmfile(TableName+".index");
    rmfile(TableName+".link");
    pop_string_to >> TableName;
    if(TableName.compare(";")!=0)
        throw QueryException("ERROR: invalid query format, except a ';' as the end of create statement!");

}

void InterManager::EXEC_DROP_INDEX()
{
    std::cout <<"into e index";
}

void InterManager::EXEC_CREATE_INDEX(){std::cout <<"create index\n";}
void InterManager::EXEC_INSERT(){
    //std::cout <<"insert\n";
    //insert into tablename values(xxxx);
    std::string Token,TableName;
    pop_string_to >> Token;
    if(Token.compare("into")!=0)
        throw QueryException("ERROR: invalid query format, except 'into' after 'insert'!");
    pop_string_to >> Token;
    if(!isexist(Token+".table"))
        throw TableException("ERROR: the table "+Token+" is not exists");
    TableName = Token;
    Table t(TableName);

    Attr attrs[MAX_ATTR];
    Tuber tuber;
    Element arr_e[MAX_ATTR];

    pop_string_to >> Token;
    if(Token.compare("values")!=0)
        throw QueryException("ERROR: invalid query format, except 'values' after table name!");
    pop_string_to >> Token;
    if(Token.compare("(")!=0)
        throw QueryException("ERROR: invalid query format, except '(' after 'values'!");
    for(int i=0;i<t.attr_length;i++){
        pop_string_to >> Token;
        PrintScreen("Token is "+Token+"\n");
        if(Token.find("'")!=Token.npos){
            attrs[i].attrtype=2;
            attrs[i].attrlength=Token.length()-2;
            //char型不读空格
        }else if(Token.find(".")!=Token.npos&&notchar(Token)){
            attrs[i].attrtype=1;
        }else if(isNum(Token)){
            attrs[i].attrtype=0;
        }else{
            throw QueryException("ERROR: invalid query format, unknown the type of "+Token+"!");
        }
        if(attrs[i].attrtype!=t.attrs[i].attrtype)
            throw QueryException("ERROR: invalid query format,the data "+Token+" can't insert into table "+TableName+"!");
        if(attrs[i].attrlength>t.attrs[i].attrlength)
            throw QueryException("ERROR: invalid query format,the data "+Token+" too long!");
        if(t.attrs[i].attrtype!=2)
            arr_e[i].set_element(t.attrs[i].attrtype,t.attrs[i].attrlength,Token);
        else{
            if(Token.length()>2)
                arr_e[i].set_element(t.attrs[i].attrtype,t.attrs[i].attrlength,Token.substr(1,Token.length()-2));
            else
                arr_e[i].set_element(t.attrs[i].attrtype,t.attrs[i].attrlength,"#");//用#代替空格
        }

        pop_string_to >> Token;//吃逗号&右括号
    }
    pop_string_to >> Token;
    if(Token.compare(";")!=0)
        throw QueryException("ERROR: invalid query format, except a ';' as the end of create statement!");
    int tuber_length=0;
    for(int i=0;i<t.attr_length;i++){
        tuber_length+=t.attrs[i].attrlength;
    }
    tuber.set_tuber(arr_e,t.attr_length,tuber_length,BlockAddr(0,0));
    tuber.pkpos=t.primary_key_pos;
    RecoderManager rm;
    tuber.e_addr=rm.RMstoredata(tuber,TableName);
    //将数据存入
}
void InterManager::EXEC_DELETE(){std::cout <<"delete\n";}
//随便删，之后由用户碎片整理
void InterManager::EXEC_SHOW(){std::cout <<"show\n";}
void InterManager::EXEC_EXIT(){
    std::cout <<"exit\n";
//    RecoderManager rm;
//    Table t("City");
//    Tuber tuber;
//    tuber=rm.RMreaddata(BlockAddr(0,8),"City",t.attrs,t.attr_length);
//    tuber.show_tuber();
}
void InterManager::EXEC_FILE(){std::cout <<"file\n";}

