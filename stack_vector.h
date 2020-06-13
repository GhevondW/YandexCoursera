#pragma once

#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0)
    :_size(a_size)
    {
        if(_size > N) throw invalid_argument{"invalid argument"};
    }

    T& operator[](size_t index)
    {
        if(_size != 0 && index >= 0 && index < _size){
            return _data[index];
        }
        throw invalid_argument{"invalid argument"};
    }
    const T& operator[](size_t index) const
    {
        if(_size != 0 && index >= 0 && index < _size){
            return _data[index];
        }
        throw invalid_argument{"invalid argument"};
    }

    T* begin(){ return _data; }
    T* end(){ return &_data[_size]; }
    const T* begin() const { return _data; }
    const T* end() const { return &_data[_size]; }

    size_t Size() const { return _size;}
    size_t Capacity() const { return CAPACITY; }

    void PushBack(const T& value)
    {
        if(_size < CAPACITY){
            _data[_size] = value;
            ++_size;
            return;
        }
        throw overflow_error{"stack overflow"};
    }
    
    T PopBack()
    {
        if(_size > 0){
            --_size;
            return _data[_size];
        }
        throw underflow_error{"stack onderflow"};
    }

private:
    size_t _size{};
    T _data[N]{};
private:
    const static size_t CAPACITY = N;
};
