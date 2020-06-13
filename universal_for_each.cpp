#if 0
//
//  universal_for_each.cpp
//  Cursera_red
//
//  Created by Ghevond Gevorgyan on 5/11/20.
//  Copyright © 2020 Ghevond Gevorgyan. All rights reserved.
//

#include <iostream>
#include <vector>

template<typename Iter>
struct IteratorRange {
    Iter _begin;
    Iter _end;
    
    Iter begin() const { return _begin; }
    Iter end() const { return _end; }
};

//bad example Head
template<typename T>
std::vector<T> BadHead(const std::vector<T>& vector, size_t n)
{
    return
    {
        vector.begin(),
        std::next(vector.begin(), std::min(vector.size(), n))
    };
}

//GOOD HEAD
template<typename T>
IteratorRange<typename std::vector<T>::iterator> Head(std::vector<T>& vector, size_t n)
{
    IteratorRange<typename std::vector<T>::iterator> result{};
    result._begin = vector.begin();
    result._end = std::next(vector.begin(), std::min(vector.size(), n));
    return result;
}

int main()
{
    
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    for(int x : Head(v,3)){
        std::cout<<x<<", ";
    }
    
    return 0;
}
#endif
