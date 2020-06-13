#include <iostream>

using namespace std;



template <typename T>
class SimpleVector {
public:
    SimpleVector();
    explicit SimpleVector(size_t size);
    ~SimpleVector();

    T& operator[](size_t index);

    T* begin();
    T* end();

    size_t Size() const;
    size_t Capacity() const;
    void PushBack(const T& value);
    void PushBack(T&& value);

  // При необходимости перегрузите
  // существующие публичные методы

private:
    
    void _Resize();
    
private:
  // Добавьте сюда поля
    T* _data{nullptr};
    size_t _size;
    size_t _capacity;
};

template<typename T>
SimpleVector<T>::SimpleVector()
:_data(nullptr),
_size(0),
_capacity(0)
{
    
}

template<typename T>
SimpleVector<T>::SimpleVector(size_t size)
:_data(new T[size]),
_size(size),
_capacity(size)
{
    
}

template<typename T>
SimpleVector<T>::~SimpleVector()
{
    if(_data != nullptr){
        delete [] _data;
    }
}

template<typename T>
T& SimpleVector<T>::operator[](size_t index)
{
    if(index >= 0 && index < _size){
        return _data[index];
    }
    throw std::out_of_range{"out of range"};
}

template<typename T>
T* SimpleVector<T>::begin()
{
    return _data;
}

template<typename T>
T* SimpleVector<T>::end()
{
    return _data ? (_data + _size) : nullptr;
}

template<typename T>
size_t SimpleVector<T>::Size() const
{
    return _size;
}

template<typename T>
size_t SimpleVector<T>::Capacity() const
{
    return _capacity;
}

template<typename T>
void SimpleVector<T>::PushBack(const T& value)
{
    if(_size == _capacity) _Resize();
    _data[_size++] = value;
}

template<typename T>
void SimpleVector<T>::PushBack(T&& value)
{
    if(_size == _capacity) _Resize();
    _data[_size++] = std::move(value);
}

template<typename T>
void SimpleVector<T>::_Resize()
{
    _capacity = _capacity == 0 ? 4 : _capacity;
    _capacity <<= 1;
    T* tmp = new T[_capacity];
    if(_data){
        std::move(begin(), end(), tmp);
        delete[] _data;
    }
    _data = tmp;
}
