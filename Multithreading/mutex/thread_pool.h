#ifndef _thread_pool_h_
#define _thread_pool_h_

#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <functional>
#include <atomic>
#include <iostream>

#define MAX(a, b) (a) > (b) ? a : b;

namespace std
{

enum mode
{
    max_perf,
    min_perf,
    balanced_perf  
};

class thread_pool
{
    using task = std::function<void()>;
public:

    thread_pool(mode m = std::balanced_perf)
    {_init(m);}

    ~thread_pool()
    { _clear();}

    thread_pool(const thread_pool&) = delete;
    thread_pool(thread_pool&&) = delete;
    void operator=(const thread_pool&) = delete;
    void operator=(thread_pool&&) = delete;

public:

    void enqueue_task(task t)
    {
        std::lock_guard<std::mutex> lk{_data_mtx};
        _tasks.push(t);
        _worker_cond.notify_one();
    }

private:

    void _init(mode m)
    {
        _stop = false;
        const size_t mcount = std::thread::hardware_concurrency();
        if(m == mode::max_perf){
            _workers_count = mcount;
        }
        else if(m == mode::min_perf){
            _workers_count = 1;
        }
        else{
            _workers_count = MAX(2, mcount>>1);
        }

        for (int i = 0; i < _workers_count; i++)
        {
            _workers.push_back(std::thread{&thread_pool::_worker, this});
        }
    }

    void _worker()
    {
        // std::cout<<"thread starts:["<<std::this_thread::get_id()<<"]"<<std::endl;
        // std::this_thread::sleep_for(std::chrono::seconds(std::rand()%8));
        // std::cout<<"End:["<<std::this_thread::get_id()<<"]"<<std::endl;
        while (true)
        {
            std::unique_lock<std::mutex> lk{_data_mtx};
            _worker_cond.wait(lk, [this]()
            {
                return this->_stop || !this->_tasks.empty();
            });

            if(_stop) return;

            task t = _tasks.front();
            _tasks.pop();
            
            lk.unlock();

            if(t != nullptr) t();
        }
        
    }

    void _clear()
    {
        _stop = true;
        for (size_t i = 0; i < _workers_count; i++)
        {
            if(_workers[i].joinable()){
                _workers[i].join();   
            }
        }
    }

private:
    size_t                      _workers_count{};
    std::queue<task>            _tasks{};
    std::mutex                  _data_mtx{};
    std::condition_variable     _worker_cond{};
    std::vector<std::thread>    _workers{};
    std::atomic<bool>           _stop{};
};

} // namespace std


#endif