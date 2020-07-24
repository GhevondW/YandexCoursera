#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <iostream>
#include <map>
#include <string>

namespace db{

enum Command
{
    ADD,
    PRINT,
    UNKNOWN,
};

struct DbRequest
{
    Command cmd;
    std::string txt;
};

DbRequest CreateRequest(std::string str)
{
    DbRequest req;
    if(str.find("PRINT") != std::string::npos){
        req.cmd = Command::PRINT;
    }
    else if(str.empty()){
        req.cmd = Command::UNKNOWN;
    }
    else{
        req.cmd = Command::ADD;
        req.txt = std::move(str);
    }
    return std::move(req);
}

class Database
{
public:
    Database(/* args */)
    :_data()
    {}

    ~Database() = default;

public:

    void Handle(DbRequest req)
    {
        
        if(req.cmd == Command::ADD){
            
            if(_data.count(req.txt)){
                
                ++_data[req.txt];
            }
            else{
                
                _data.insert({std::move(req.txt), 0});
            }
        }
        else if(req.cmd == Command::PRINT){
            
            Print();
        }
    }

private:

    void Print()
    {
        if(_data.size() != 0){
            auto c = begin(_data);
            while (c != std::end(_data))
            {
                std::cout<<"["<<c->first<<":"<<c->second<<"]"<<std::endl;
                ++c;
            }
        }
        else{
            std::cout<<"EMPTY DB"<<std::endl;
        }
    }

private:
    std::map<std::string, int> _data;
};


};

#endif