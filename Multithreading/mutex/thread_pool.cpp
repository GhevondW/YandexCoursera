#include "thread_pool.h"
#include <iostream>

std::mutex m;

void task(int a)
{
    {std::lock_guard<std::mutex> l{m};
    std::cout<<"thread starts:["<<a<<"]"<<std::endl;
    }   
    
    std::this_thread::sleep_for(std::chrono::seconds(std::rand()%20));
    {std::lock_guard<std::mutex> l{m};
    std::cout<<"End:["<<a<<"]"<<std::endl;
    }
}

static std::thread_pool pool{std::mode::max_perf};

int main()
{

    for (int i = 0; i < 20; i++)
    {
        pool.enqueue_task([i]()
        {
            task(i);
        });
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(1522222));

    return 0;
}