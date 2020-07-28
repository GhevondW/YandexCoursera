//
//  ThreadPool.h
//  Net
//
//  Created by Ghevond Gevorgyan on 7/27/20.
//  Copyright © 2020 Ghevond Gevorgyan. All rights reserved.
//

#ifndef ThreadPool_h
#define ThreadPool_h

#include <stdlib.h>
#include <array>
#include <thread>
#include <functional>
#include <queue>

using Task = std::function<void()>;

template<size_t N>
class ThreadPool
{
public:
    ThreadPool();
    ~ThreadPool();
    
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;
    
public:
    
    void EnqueueTask(Task&& task);
    
private:
    
    bool _Init();
    void _ThreadLife();
    void _SendStopSignal();
    void _Cleanup();
    
private:
    const size_t                _MaxThreadCount{N};
    std::array<std::thread, N>  _threads{};
    std::queue<Task>            _tasks{};
    std::mutex                  _tasks_lock{};
    std::atomic<bool>           _stop_signal{false};
};

template<size_t N>
ThreadPool<N>::ThreadPool()
{
    if(!_Init())
    {
        throw std::bad_alloc{};
    }
}

template<size_t N>
ThreadPool<N>::~ThreadPool()
{
    _SendStopSignal(); //STOP WHILE LOOP
    _Cleanup(); //JOIN
}

template<size_t N>
void ThreadPool<N>::EnqueueTask(Task&& task)
{
    std::lock_guard<std::mutex> lock(_tasks_lock);
    _tasks.push(task);
}

template<size_t N>
bool ThreadPool<N>::_Init()
{
    try {
        _stop_signal = false;
        for (size_t i = 0; i < N; ++i) {
            _threads[i] = std::thread{&ThreadPool::_ThreadLife, this};
        }
    } catch (std::exception){
        return false;
    }
    return true;
}

template<size_t N>
void ThreadPool<N>::_ThreadLife()
{
    while (true) {
        
        Task task{nullptr};
        
        if(_stop_signal){
            break;
        }
        
        _tasks_lock.lock();
        if(!_tasks.empty()){
            task = _tasks.front();
            _tasks.pop();
        }
        _tasks_lock.unlock();
        
        if(task != nullptr){
            task();
        }
        
    }
}

template<size_t N>
void ThreadPool<N>::_SendStopSignal()
{
    _stop_signal = true;
}

template<size_t N>
void ThreadPool<N>::_Cleanup()
{
    for (int i = 0; i < N; ++i) {
        if(_threads[i].joinable()){
            _threads[i].join();
        }
    }
}


#endif /* ThreadPool_h */
