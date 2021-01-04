#include <iostream>
#include <memory>
#include <utility>
#include "Handler.h"
using namespace std;

int main()
{
    Message msg{"Hello", LEVEL::THREE};

    HandlerBase handler;
    handler.AddNext(std::unique_ptr<HandlerOne>(new HandlerOne()));
    handler.AddNext(std::unique_ptr<HandlerTwo>(new HandlerTwo()));
    handler.AddNext(std::unique_ptr<HandlerThree>(new HandlerThree()));

    handler.HandleMessage(msg);

    return 0;
}