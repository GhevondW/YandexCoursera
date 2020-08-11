#ifndef _hierarchical_mutex_h_
#define _hierarchical_mutex_h_

#include <mutex>
#include <thread>
#include <limits.h>
#include <stdexcept>
#include <string>

using ulong = unsigned long;
using uint  = unsigned int;


class hierarchical_mutex
{
public:
    explicit hierarchical_mutex(ulong value)
    :_hierarchy_value(value),
    _prev_hierarchy_value(0){}

    ~hierarchical_mutex() = default;

public:

    void lock()
    {
        _CheckForHierarchyViolation();
        _mutex.lock();
        _UpdateHierarchyValue();
    }

    void unlock()
    {
        _this_thread_hierarchy_value = _prev_hierarchy_value;
        _mutex.unlock();
    }

    bool try_lock()
    {
        _CheckForHierarchyViolation();
        if(!_mutex.try_lock()){
            return false;
        }
        _UpdateHierarchyValue();
        return true;
    }

private:

    void _UpdateHierarchyValue()
    {
        _prev_hierarchy_value = _this_thread_hierarchy_value;
        _this_thread_hierarchy_value = _hierarchy_value;
    }

    void _CheckForHierarchyViolation()
    {
        if(_this_thread_hierarchy_value <= _hierarchy_value){
            throw std::logic_error{"mutex hierarchy violated"};
        }
    }

private:

    std::mutex                  _mutex;
    const ulong                 _hierarchy_value;
    uint                        _prev_hierarchy_value;
    static thread_local ulong   _this_thread_hierarchy_value;

};

thread_local ulong hierarchical_mutex::_this_thread_hierarchy_value(ULONG_MAX);

#endif