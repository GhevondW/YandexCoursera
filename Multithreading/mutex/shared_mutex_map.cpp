#include <iostream>
#include <shared_mutex>
#include <unordered_map>
#include <mutex>
#include <random>
#include <functional> //for std::function
#include <algorithm>  //for std::generate_n
#include <list>
#include <string>
#include <thread>
#include "profile.h"

#define TEST 1
#define SHARED_LOCK 0

//g++ shared_mutex_map.cpp -o main.out -std=c++17 -pthread

class Database
{
public:

    Database()
    {
        #if TEST
            // std::call_once(_once_flag, [this](){
                _Init();
            // });
        #endif
    }

    ~Database() = default;

private:

#if TEST
    void _Init()
    {
        for (size_t i = 0; i < 10000000; i++)
        {
            std::string s = _GetRandString(10);
            _urls.push_back(s);
            ++_data[s];
        }
        std::cout<<"Init: size="<<_data.size()<<std::endl;   
    }

    std::string _GetRandString( size_t length )
    {
        auto randchar = []() -> char
        {
            const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[ rand() % max_index ];
        };
        std::string str(length,0);
        std::generate_n( str.begin(), length, randchar );
        return str;
    }

public:

    const std::vector<std::string>& GetStrings()
    {
        return _urls;
    }

#endif

    size_t GetValByUrl(const std::string& url) const
    {
        #if SHARED_LOCK 
        std::shared_lock<std::__shared_mutex_pthread> _lock(_data_lock);
        #else
        std::lock_guard<std::__shared_mutex_pthread> _lock(_data_lock);
        #endif
        auto f = _data.find(url);
        return f != end(_data) ? f->second: 0;
    }

    void ChangeValue(const std::string& url, size_t new_value)
    {
        std::lock_guard<std::__shared_mutex_pthread> _lock(_data_lock);
        auto f = _data.find(url);
        if(f != end(_data)){
            f->second = new_value;
        }
    }

private:
    std::vector<std::string>                        _urls;
    std::unordered_map<std::string, size_t>         _data;
    mutable std::__shared_mutex_pthread             _data_lock;
    // std::once_flag                                  _once_flag;
};

void Run(int begin, int end, const Database& db, const std::vector<std::string>& urls)
{
    for (size_t i = begin; i < end; i++)
    {
        db.GetValByUrl(urls[i]);
    }
}

int main()
{

#if TEST

    std::cout<<"Shared mutex"<<std::endl;

    
    Database db{};
    

    auto urls = db.GetStrings();

    int size = urls.size();
    const int max_thread_count = std::thread::hardware_concurrency() - 2; 

    std::cout<<max_thread_count<<std::endl;

    const int slice_size = size / max_thread_count;
    std::vector<std::thread> threads;

{LOG_DURATION("Test")
    for (size_t i = 0; i < max_thread_count; i++)
    {
        int b = i * slice_size;
        int e = b + slice_size;
        threads.push_back(std::thread{Run, b, e, std::ref(db), std::ref(urls)});
    }
   
    for (size_t i = 0; i < max_thread_count; i++)
    {
        if(threads[i].joinable())
        {
            threads[i].join();
        }
    }
}   

#endif

    return 0;
}