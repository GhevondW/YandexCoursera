#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <string>
#include <iostream>

enum LEVEL
{
    ONE = 1,
    TWO = 2,
    THREE = 3
};

class Message
{
private:
    std::string _message;
    LEVEL _level{};
public:
    Message(/* args */) = default;
    Message(const std::string& msg, LEVEL level)
    :_message(msg),
    _level(level)
    {}
    ~Message() = default;

    void PrintMessage() const
    {
        std::cout<<"Message:"<<_message<<", Level:"<<(int)_level<<std::endl;
    }

    LEVEL GetLevel() const { return _level; }

};


#endif