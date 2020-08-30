#include <iostream>
#include "profile.h"
#include "threadsafe_queue.h"
#include <thread>

TSQueue<std::string> tsq;

void Input()
{
    std::string command;
    while (true)
    {
        std::getline(std::cin, command);
        if(command == "END"){
            break;
        }
        tsq.Push(command);
        PrintMsg(std::to_string(tsq.Size()));
    }
    
}

void Output()
{
    while (true)
    {
        // std::string res;
        auto res = tsq.WaitPop();
        
        std::cout<<5<<std::endl;
    }
    
}

int main(){

    std::thread t1{[](){
        Input();
    }};
    std::thread t2{[](){
        Output();
    }};


    t1.join();
    t2.join();

    return 0;
}