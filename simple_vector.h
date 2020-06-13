#pragma once

#include <cstdlib>
#include <algorithm>


template <typename T>
class SimpleVector {
public:
    SimpleVector()
    :_data(nullptr),
    _size(0),
    _capacity(0)
    {
        
    }
    
    explicit SimpleVector(size_t size)
    :_data(nullptr),
    _size(size),
    _capacity(CAPACITY)
    {
        _Init();
    }
    
    SimpleVector(const SimpleVector<T>& other)
    :_data(new T[other._capacity]),
    _capacity(other._capacity),
    _size(other._size)
    {
        copy(other.begin(), other.end(), begin());
    }
    
    SimpleVector(SimpleVector<T>&& other)
    :_data(other._data),
    _capacity(other._capacity),
    _size(other._size)
    {
        other._data = nullptr;
        other._capacity = other._size = 0;
    }
    
    ~SimpleVector(){
        if(_data != nullptr)
        {
            delete[] _data;
            _data = nullptr;
        }
    }
    
    T& operator[](size_t index)
    {
        if(index >= 0 && index < _size)
        {
            return _data[index];
        }
        throw "out of range";
    }
    
    SimpleVector& operator=(const SimpleVector<T>& other)
    {
        if(_capacity >= other._size){
            _size = other._size;
        }
        else{
            if(_data != nullptr){
                delete[] _data;
            }
            _capacity = other._capacity;
            _data = new T[other._capacity];
            _size = other._size;
        }
        
        std::memcpy(_data, other._data, sizeof(T)*_size);
        
        return *this;
    }
    
    SimpleVector* operator=(SimpleVector<T>&& other)
    {
        if(_data != nullptr){
            delete[] _data;
        }
        _data = other._data;
        _capacity = other._capacity;
        _size = other._size;
        
        other._data = nullptr;
        other._capacity = other._size = 0;
    }
    
    T* begin(){return _data;}
    T* end(){return (_data + _size);}
    
    const T* begin() const {return _data;}
    const T* end() const {return (_data + _size);}
    
    size_t Size() const {return _size;}
    size_t Capacity() const {return _capacity;}
    
    void PushBack(const T& value)
    {
        
        if(_size >= _capacity){
            _Resize();
        }
        _data[_size] = value;
        ++_size;
    }

private:
    
    void _Init()
    {
        if(_capacity < _size){
            int c = _size % _capacity + 2;
            _capacity *= c;
        }
        _data = new T[_capacity];
    }
    
    void _Resize()
    {
        _capacity = _capacity ? _capacity * 2 : CAPACITY;
        T* new_mem = new T[_capacity];
        for (int i = 0; i < _size; ++i) {
            new_mem[i] = _data[i];
        }
        delete[] _data;
        _data = new_mem;
    }
    
private:
    T* _data;
    int _size{};
    int _capacity{};
    
private:
    const static size_t CAPACITY = 16;
};
