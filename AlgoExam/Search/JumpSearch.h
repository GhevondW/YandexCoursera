#ifndef _JUMP_SEARCH_H_
#define _JUMP_SEARCH_H_

#include <utility>
#include <cmath>
#include "Defines.h"

template<class T>
int JumpSearch(const T* const arr, size_t size, const T& val, size_t jump = 0)
{
    if(jump == 0)
    {
        jump = std::sqrt(size);
    }

    if(jump >= size) throw "Invalid Param";

    int current = 0;
    while (true)
    {
        if(arr[current] == val) return current;
        if(current == 0 && arr[current] > val) return - 1;

        if(arr[current] > val){
            for (size_t i = 1; i < jump; i++)
            {
                if(arr[current - i] == val){
                    return current - i;
                }
            }
        }
        else{
            if(current == size - 1) break;
            current += jump;
            current =  MIN(size - 1, current);
        }
    }
    

    return -1;
}

#endif