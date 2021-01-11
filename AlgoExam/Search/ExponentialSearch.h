#ifndef _EXPONENTIAL_SEARCH_H_
#define _EXPONENTIAL_SEARCH_H_

#include "BinarySearch.h"

template<class T>
int ExponentialSearch(const T* const arr, size_t size, const T& val)
{
    int pos = 0;
    if(arr[pos] == val) return pos;
    if(arr[pos] > val) return -1;

    pos = 1;
    while (pos < size && arr[pos] <= val)
        pos = pos*2;
    
    return BinarySearch(arr, pos >> 1, MIN(pos, size - 1), val);
}

#endif