#if 0
#include <iostream>
#include <vector>
#include <stdexcept>

template<class T>
class Deque
{
#define RET(fsize, index) return fsize > index ? _front[fsize - 1 - index] : _back[index -  fsize];
    
#define AT(index) \
    size_t size = Size();\
    if(index >= 0 && index < size){\
        return this->operator[](index);\
    }\
    throw std::out_of_range{"out of range"};
    
#define __validate(x, size) (x >= 0 && x < size)
    
public:
    Deque()
    :_front(),
    _back(),
    _size(0)
    {}
    Deque(const Deque& other)
    :_front(other._front),
    _back(other._back),
    _size(other._size)
    {}
    ~Deque(){}
    
public:
    
    size_t Size() const { return _size; }
    bool Empty() const { return _size == 0; }
    
    void PushFront(const T& val){
        _front.push_back(val);
        ++_size;
    }
    
    void PushBack(const T& val){
        _back.push_back(val);
        ++_size;
    }
    
    T& operator[](const size_t index){
        size_t fsize = _front.size();
        if(Size() != 0){
            RET(fsize, index);
        }
        return _front[0];
    }
    
    const T& operator[](const size_t index) const{
        size_t fsize = _front.size();
        if(Size() != 0){
            RET(fsize, index);
        }
        return _front[0];
    }
    
    T& At(size_t index){ AT(index); }
    const T& At(size_t index) const { AT(index); }
    
    const T& Front() const{
        return At(0);
    }
    
    const T& Back() const{
        return At(Size() - 1);
    }
    
    T& Front(){
        return At(0);
    }
    
    T& Back(){
        return At(Size() - 1);
    }
    
private:
    std::vector<T> _front;
    std::vector<T> _back;
    size_t _size;
};

int main(){
    
    Deque<int> d;
    d.PushBack(0);
    d.PushBack(5);
    d.PushBack(6);
    d.PushFront(1);
    d.PushFront(2);
    d.PushFront(1);
    d.PushFront(1);
    
    //1, 1, 2, 1, 0, 5, 6
    
    const Deque<int> a{d};
    d.Front() = 65;
    std::cout<<d.At(0)<<std::endl;
    std::cout<<d.At(1)<<std::endl;
    std::cout<<d.At(2)<<std::endl;
    std::cout<<d.At(3)<<std::endl;
    std::cout<<d.At(4)<<std::endl;
    std::cout<<d.At(5)<<std::endl;
    std::cout<<d.At(6)<<std::endl;
    
    std::cout<<d.Front()<<std::endl;
    std::cout<<a.Front()<<std::endl;
    
    std::cout<<d.Back()<<std::endl;
    std::cout<<a.Back()<<std::endl;
    
    return 0;
}
#endif
