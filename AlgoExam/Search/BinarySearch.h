#ifndef _BINARY_SEARCH_H_
#define _BINARY_SEARCH_H_

#include <utility>
#include "Defines.h"

template<class T>
int BinarySearch(const T* const arr, size_t begin, size_t end, const T& val)
{

    if(end < begin) return -1;

    int mid = begin + (end - begin) / 2;

    if(arr[mid] == val){
        return mid;
    }
    else if(arr[mid] > val){
        return BinarySearch(arr, begin, mid - 1, val);
    }
    else{
        return BinarySearch(arr, mid + 1, end, val);
    }

    return -1;
}

#endif