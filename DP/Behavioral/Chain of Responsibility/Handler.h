#ifndef _HANDLER_H_
#define _HANDLER_H_

#include <memory>
#include "Message.h"

class HandlerBase
{
protected:
    std::unique_ptr<HandlerBase> _next{nullptr};
public:
    HandlerBase(/* args */) = default;
    HandlerBase(std::unique_ptr<HandlerBase> next)
    :_next(std::move(next))
    {}
    virtual ~HandlerBase() = default;

    virtual void HandleMessage(const Message& msg)
    {
        if(_next){
            _next->HandleMessage(msg);
        }
    }

    virtual void AddNext(std::unique_ptr<HandlerBase> next)
    {
        if(_next == nullptr){
            _next = std::move(next);
        }
        else{
            _next->AddNext(std::move(next));
        }
    }

};

class HandlerOne : public HandlerBase
{
private:
    /* data */
public:
    HandlerOne(/* args */) = default;
    HandlerOne(std::unique_ptr<HandlerBase> next)
    :HandlerBase(std::move(next))
    {}
    ~HandlerOne() = default;

    void HandleMessage(const Message& msg) override
    {
        if(msg.GetLevel() == LEVEL::ONE){
            std::cout<<"[H_ONE] ";
            msg.PrintMessage();
            return;
        }
        HandlerBase::HandleMessage(msg);
    }

};

class HandlerTwo : public HandlerBase
{
private:
    /* data */
public:
    HandlerTwo(/* args */) = default;
    HandlerTwo(std::unique_ptr<HandlerBase> next)
    :HandlerBase(std::move(next))
    {}
    ~HandlerTwo() = default;

    void HandleMessage(const Message& msg) override
    {
        if(msg.GetLevel() == LEVEL::TWO){
            std::cout<<"[H_TWO] ";
            msg.PrintMessage();
            return;
        }
        HandlerBase::HandleMessage(msg);
    }

};

class HandlerThree : public HandlerBase
{
private:
    /* data */
public:
    HandlerThree(/* args */) = default;
    HandlerThree(std::unique_ptr<HandlerBase> next)
    :HandlerBase(std::move(next))
    {}
    ~HandlerThree() = default;

    void HandleMessage(const Message& msg) override
    {
        if(msg.GetLevel() == LEVEL::THREE){
            std::cout<<"[H_THREE] ";
            msg.PrintMessage();
            return;
        }
        HandlerBase::HandleMessage(msg);
    }

};

#endif