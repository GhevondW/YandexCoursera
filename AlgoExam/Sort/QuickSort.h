#ifndef _QUICK_SORT_H_
#define _QUICK_SORT_H_

#include <utility>
#include "Defines.h"
#include <vector>
#include <iostream>

template<class T, class Comparator>
int _Partition(std::vector<T>& data, const int begin, const int end, Comparator comp)
{
    const T& pivot = data[end];

    int j = begin - 1;
    for (size_t i = begin; i <= end - 1; ++i)
    {
        if(comp(data[i], pivot)){
            ++j;
            std::swap(data[i], data[j]);
        }
    }
    std::swap(data[j + 1], data[end]);
    return (j + 1);
}

template<class T, class Comparator>
void _QuickSort(std::vector<T>& data, const int begin, const int end, Comparator comp)
{
    if(end > begin){
        auto partition = _Partition(data, begin, end, comp);
        _QuickSort(data, begin, partition - 1, comp);
        _QuickSort(data, partition + 1, end, comp);
    }
}

template<class T, class Comparator>
void QuickSort(std::vector<T>& data, Comparator comp)
{
    std::cout<<"Quick Sort"<<std::endl;
    _QuickSort(data, 0, (int)(data.size() - 1), comp);
}

#endif