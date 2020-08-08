#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>

//this is the example of std::lock function it alows us to lock multiple mutexes 
//at same time without deadlocking
#define COMBINE(X,Y) X##Y 
#define ADOPTLOCK(m, line) std::lock_guard<std::mutex> COMBINE(adoptlock, line)(m, std::adopt_lock);
#define LOCK(m, line) std::lock_guard<std::mutex> COMBINE(reglock, line)(m);

class Data
{
public:
    Data() = default;
    Data(int val):_value(val){}
    
private:
    int _value{};
};

class DataWrapper
{
    friend void Swap(DataWrapper&, DataWrapper&);
public:
    DataWrapper() = default;
    DataWrapper(const Data& data):_data(data){}
    ~DataWrapper(){};

private:
    Data _data{};
    std::mutex _lock{};
};

void Swap(DataWrapper& ldata, DataWrapper& rdata)
{
    if(&ldata == &rdata) return;
    std::lock(ldata._lock, rdata._lock);
    ADOPTLOCK(ldata._lock, __LINE__);
    ADOPTLOCK(rdata._lock, __LINE__);

    std::cout<<"[SWAP]"<<std::endl;

    decltype(ldata._data) tmp = ldata._data;
    ldata._data = rdata._data;
    rdata._data = tmp;
}

int main()
{

    DataWrapper dw1{{5}};
    DataWrapper dw2{{5}};
    DataWrapper dw3{{5}};

    std::atomic<bool> stop{false};

    std::mutex print_lock;

    std::thread t1{[&](){
        std::cout<<"Thread1 start"<<std::endl;
        while (!stop)
        {
            Swap(dw1, dw2);
            // std::cout<<"[SWAP1]"<<std::endl;
            // std::this_thread::sleep_for(std::chrono::seconds(std::rand()%10));
        }
        std::cout<<"Thread1 end"<<std::endl;
    }};

    std::thread t2{[&](){
        std::cout<<"Thread2 start"<<std::endl;
        while (!stop)
        {
            Swap(dw2, dw3);
            // std::cout<<"[SWAP2]"<<std::endl;
            // std::this_thread::sleep_for(std::chrono::seconds(std::rand()%10));
        }
        std::cout<<"Thread2 end"<<std::endl;
    }};

    std::thread t3{[&](){
        std::cout<<"Thread3 start"<<std::endl;
        while (!stop)
        {
            Swap(dw1, dw3);
            // std::cout<<"[SWAP3]]"<<std::endl;
            // std::this_thread::sleep_for(std::chrono::seconds(std::rand()%10));
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