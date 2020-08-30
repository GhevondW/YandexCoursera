#ifndef _threadsafe_queue_h_
#define _threadsafe_queue_h_

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <memory>

template<class T>
class TSQueue
{
public:
    TSQueue() = default;
    ~TSQueue() = default;
    TSQueue(const TSQueue& other) = delete;
    TSQueue(TSQueue&& other) = delete;
    void operator=(const TSQueue& other) = delete;
    void operator=(TSQueue&& other) = delete;

public:

    auto Size() const -> size_t
    {
        std::lock_guard<std::mutex> lock(_mtx_data);
        return _data.size();
    }
    auto Empty() const -> bool
    {
        std::lock_guard<std::mutex> lock(_mtx_data);
        return _data.empty();
    }
    
    auto Push(const T& val) -> void
    {
        std::lock_guard<std::mutex> l{_mtx_data};
        _data.push(val);
        _read_cond.notify_one();
    }

    auto Push(T&& val) -> void
    {
        std::lock_guard<std::mutex> l{_mtx_data};
        _data.push(val);
        _read_cond.notify_one();
    }

    auto TryPop(T& ret) -> bool
    {
        std::lock_guard<std::mutex> l{_mtx_data};
        if(!Empty()){
            ret = _data.front();
            _data.pop();
            return true;
        }
        return false;
    }

    auto TryPop() -> std::shared_ptr<T>
    {
        std::lock_guard<std::mutex> l{_mtx_data};
        if(Empty()) return std::make_shared<T>(nullptr);

        std::shared_ptr<T> ret{std::make_shared<T>(_data.front)};
        _data.pop();
        return ret;
    }

    auto WaitPop(T& ret) -> void
    {
        std::unique_lock<std::mutex> lk(_mtx_data);
        _read_cond.wait(lk, [this]()
        {
            return !this->_data.empty();
        });

        ret = _data.front();
        _data.pop();
        lk.unlock();
    }

    auto WaitPop() -> std::shared_ptr<T>
    {
        std::unique_lock<std::mutex> lk;
        _read_cond.wait(lk,[this]()
        {
            return !this->_data.empty();
        });
        std::shared_ptr<T> tmp{std::make_shared<T>(_data.front())};
        _data.pop();
        return tmp;
    }

    

private:
    std::queue<T>               _data;
    mutable std::mutex          _mtx_data;
    std::condition_variable     _read_cond;
};

#endif