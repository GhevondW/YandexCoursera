#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

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
    //std::defer_lock allows us do not lock the mutex in construto
    //unique lock has this interface
    //1)lock()
    //2)unlock()
    //3)try_lock()
    //it is same as mutex's interface
    std::unique_lock<std::mutex> ll(ldata._lock, std::defer_lock);
    std::unique_lock<std::mutex> rl(rdata._lock, std::defer_lock);
    std::lock(ll, rl);

    std::cout<<"[SWAP]"<<std::endl;

    decltype(ldata._data) tmp = ldata._data;
    ldata._data = rdata._data;
    rdata._data = tmp;
}

using namespace  std;

int main(){

    std::cout<<"[UNIQUE LOCK]"<<std::endl;

    //we can use unique_lock as lock guard also 
    //we can use it as unique locking mechanizm
    //it alows as to do more than lock_guard

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