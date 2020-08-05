#include <iostream>
#include <thread>
#include <mutex>
#include <stack>
#include <memory>

#define LOCK_SCOPE(m) std::lock_guard<std::mutex> _lock{m};

template<class T>
class ThreadSafeStack
{
public:
    ThreadSafeStack(/* args */);
    ThreadSafeStack(const ThreadSafeStack& other);
    void operator=(const ThreadSafeStack& other) = delete;
    ~ThreadSafeStack() = default;

    void                Push(T value);
    std::shared_ptr<T>  Pop();
    void                Pop(T& value);
    bool                Empty() const;

private:
    std::stack<T>       _data;
    mutable std::mutex  _data_mutex;
};

template<class T>
ThreadSafeStack<T>::ThreadSafeStack()
{}

template<class T>
ThreadSafeStack<T>::ThreadSafeStack(const ThreadSafeStack& other)
{
    LOCK_SCOPE(_data_mutex);
    this->_data = other._data;
}

template<class T>
void ThreadSafeStack<T>::Push(T value)
{
    LOCK_SCOPE(_data_mutex);
    _data.push(std::move(value));
}

template<class T>
std::shared_ptr<T> ThreadSafeStack<T>::Pop()
{
    LOCK_SCOPE(_data_mutex);
    if(_data.empty()) throw "Empty stack";
    const auto res = std::make_shared<T>(_data.top());
    _data.pop();
    return res;
} 

template<class T>
void ThreadSafeStack<T>::Pop(T& value)
{
    LOCK_SCOPE(_data_mutex);
    if(_data.empty()) throw "Empty stack";
    value = _data.top();
    _data.pop();
} 

template<class T>
bool ThreadSafeStack<T>::Empty() const
{
    LOCK_SCOPE(_data_mutex);
    return _data.empty();
}

int main(){
    std::cout<<"Thread Safe Stack"<<std::endl;

    ThreadSafeStack<int> s;

    s.Push(5);
    s.Push(2);
    s.Push(3);
    s.Push(4);

    auto res = s.Pop();

    std::cout<<*res<<std::endl;

    int d{};
    s.Pop(d);

    std::cout<<d<<std::endl;

    
    std::cout<<s.Empty()<<std::endl;

    return 0;
}