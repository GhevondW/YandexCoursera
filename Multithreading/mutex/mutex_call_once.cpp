#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <array>

//this object need to be constructed one time 
//and this is a const shared data for multiple threads
//we need to init it only one time

#define SLEEP_S(v) std::this_thread::sleep_for(std::chrono::seconds(v))
#define SLEEP_MS(v) std::this_thread::sleep_for(std::chrono::milliseconds(v))

struct ServerConnection
{
    ServerConnection()
    {
        std::cout<<"Connectiong..."<<std::endl;
        SLEEP_S(2);
    }

    void DoWork()
    {
        std::cout<<"..."<<std::endl;
    }

};

std::shared_ptr<ServerConnection> connection;
std::once_flag connection_once_flag;

void InitConnection()
{
    connection = std::make_shared<ServerConnection>();
}

void Connect()
{   
    std::call_once(connection_once_flag, InitConnection);
    connection->DoWork();
}

using namespace std;

#define N 8

int main()
{

    array<thread, N> threads;

    for (size_t i = 0; i < N; i++)
    {
        threads[i] = thread{Connect};
    }
    


    auto c = begin(threads);
    while (c != end(threads))
    {
        c->join();
        ++c;
    }
    

    return 0;
}