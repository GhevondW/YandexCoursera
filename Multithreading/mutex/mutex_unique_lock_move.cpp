#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>

using namespace std;


class SomeData
{
public:
    SomeData()  = default;
    ~SomeData() = default;


public:

    void Function()
    {
        {
            unique_lock<mutex> lock = GetLock();
            cout<<"[Function]"<<endl;
        }
    }

private:

    void _DoSomething()
    {
        cout<<"[DoSomething]"<<endl;
        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }

    unique_lock<mutex> GetLock()
    {
        unique_lock<mutex> ul{_data_lock}; //local temp variable this will be moved
        cout<<"[GetLock]"<<endl;
        _DoSomething();
        return ul;
    }

private:
    int         _data_int{};
    double      _data_double{};
    std::mutex  _data_lock{};
};



int main(){

    
    SomeData data{};

    std::atomic<bool> stop{false};

    std::mutex print_lock;

    std::thread t1{[&](){
        std::cout<<"Thread1 start"<<std::endl;
        while (!stop)
        {
            data.Function();
        }
        std::cout<<"Thread1 end"<<std::endl;
    }};

    std::thread t2{[&](){
        std::cout<<"Thread2 start"<<std::endl;
        while (!stop)
        {
            data.Function();
        }
        std::cout<<"Thread2 end"<<std::endl;
    }};

    std::thread t3{[&](){
        std::cout<<"Thread3 start"<<std::endl;
        while (!stop)
        {
            data.Function();
        }
        std::cout<<"Thread3 end"<<std::endl;
    }};

    std::string cmd{};
    while (true)
    {
        std::getline(std::cin, cmd);
        if(cmd == "STOP"){
            stop = true;
            break;
        }
    }

    t1.join();
    t2.join();
    t3.join();

    return 0;
}