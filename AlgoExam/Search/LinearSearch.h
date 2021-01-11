#ifndef _LINEAR_SEARCH_H_
#define _LINEAR_SEARCH_H_

#include <utility>
#include "Defines.h"

template<class T>
int LinearSearch(const T* const arr, size_t size, const T& val)
{
    for (size_t i = 0; i < size; i++)
    {
        if(arr[i] == val){
            return i;
        }
    }
    return -1;
}

#endif