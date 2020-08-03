#include <iostream>
#include <mutex>
#include <thread>
#include <cstring>
#include <vector>

class SomeData
{    
public:
    SomeData(/* args */) = default;
    ~SomeData() = default;

    void DoSomething(){
        _str += "a";
        _int += 1;
        std::cout<<"["<<std::this_thread::get_id()<<"]"<<_str<<_int<<std::endl;
    }

private:
    std::string     _str{};
    int             _int{0};
};

class SomeDataWrapper
{
public:
    SomeDataWrapper(const SomeData& data):_data(data){}
    ~SomeDataWrapper() = default;

    template<class FUNCTION>
    void Process(FUNCTION func)
    {
        std::lock_guard<std::mutex> lock(_data_mutex);
        func(_data);
    }

private:
    SomeData        _data;
    std::mutex      _data_mutex;
};


using namespace std;


int  main(){

    std::cout<<"some data wrapper"<<std::endl;

    
    SomeDataWrapper wrapper{SomeData{}};

    std::vector<std::thread> tasks;

    for (size_t i = 0; i < 10; i++)
    {
        tasks.emplace_back([&](){
            wrapper.Process([](SomeData& d){
                d.DoSomething();
            });
        });
    }
    
    for (size_t i = 0; i < 10; i++)
    {
        tasks[i].join();
    }

    return 0;
}