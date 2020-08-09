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

    int GetInt() const { return _int; }

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


class SomeDataWrapperTwo
{
public:

    struct ReadAccess
    {
    public:
        ReadAccess(const SomeData& ref, std::mutex& mref)
        :_data(ref),
        _mref(mref){}
        ReadAccess(const ReadAccess& other) = default;
        ~ReadAccess(){ _mref.unlock(); }

        const SomeData& _data;
    private:
        std::mutex&     _mref;
    };

    struct WriteAccess
    {
    public:
        WriteAccess(SomeData& ref, std::mutex& mref)
        :_data(ref),
        _mref(mref){}
        WriteAccess(const WriteAccess& other) = default;
        ~WriteAccess(){ _mref.unlock(); }

        SomeData& _data;
    private:
        std::mutex&     _mref;
    };

public:
    SomeDataWrapperTwo() = default;
    SomeDataWrapperTwo(const SomeData& data):_data(data){}
    ~SomeDataWrapperTwo() = default;

    ReadAccess GetRead() const
    {
        _data_mutex.lock();
        return {_data, _data_mutex};
    }

    WriteAccess GetWrite()
    {
        _data_mutex.lock();
        return {_data, _data_mutex};
    }


private:
    SomeData                _data;
    mutable std::mutex      _data_mutex;
};


using namespace std;


int  main(){

    std::cout<<"some data wrapper"<<std::endl;

    
    SomeDataWrapper wrapper{SomeData{}};
    SomeDataWrapperTwo wrapper_two{SomeData{}};

    std::vector<std::thread> tasks;

    //FIRST WRAPPER USAGE EXAMPLE
    // for (size_t i = 0; i < 10; i++)
    // {
    //     tasks.emplace_back([&](){
    //         wrapper.Process([](SomeData& d){
    //             d.DoSomething();
    //         });
    //     });
    // }
    
    //SECOND WRAPPER USAGE EXAMPLE

    for (size_t i = 0; i < 10; i++)
    {
        tasks.emplace_back([&](){
            std::this_thread::sleep_for(std::chrono::seconds(std::rand()%10));
            {
                wrapper_two.GetWrite()._data.DoSomething();
            }
            {
                std::cout<<wrapper_two.GetRead()._data.GetInt()<<std::endl;
            }
        });
    }
    

    for (size_t i = 0; i < 10; i++)
    {
        tasks[i].join();
    }

    return 0;
}