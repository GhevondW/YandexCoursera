#ifndef _MERGE_SORT_H_
#define _MERGE_SORT_H_

#include <utility>
#include <vector>
#include <iostream>
#include "Defines.h"

template<class T, class Comparator>
void _Merge(std::vector<T>& data, const size_t left, const size_t middle, const size_t right, Comparator comp)
{
    size_t length_left = middle - left + 1;
    size_t length_right = right - middle;
    std::vector<T> left_temp(length_left);
    std::vector<T> right_temp(length_right);

    for (size_t i = 0; i < length_left; i++)
    {
        left_temp[i] = data[left + i];
    }
    for (size_t i = 0; i < length_right; i++)
    {
        right_temp[i] = data[middle + 1 + i];
    }
    
    int index_left = 0;
    int index_right = 0;
    for (size_t i = left; i <= right; i++)
    {
        if(index_left == length_left)
        {
            data[i] = right_temp[index_right];
            ++index_right;
            continue;
        }

        if(index_right == length_right)
        {
            data[i] = left_temp[index_left];
            ++index_left;
            continue;
        }

        if(comp(left_temp[index_left], right_temp[index_right]))
        {
            data[i] = left_temp[index_left];
            ++index_left;
        }
        else{
            data[i] = right_temp[index_right];
            ++index_right;
        }
    }
}

template<class T, class Comparator>
void _MergeSort(std::vector<T>& data, size_t l, size_t r, Comparator comp)
{
    if(l>=r) return;
    size_t middle = (l+r-1)/2;
    _MergeSort(data, l, middle, comp);
    _MergeSort(data, middle + 1, r, comp);
    _Merge(data, l, middle, r, comp);
}

template<class T, class Comparator>
void MergeSort(std::vector<T>& data, Comparator comp)
{
    _MergeSort(data, 0, data.size() - 1, comp);
}

#endif