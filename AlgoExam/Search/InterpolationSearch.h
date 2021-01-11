#ifndef _INTERPOLATION_SEARCH_H_
#define _INTERPOLATION_SEARCH_H_

#include <utility>
#include "Defines.h"

template<class T>
int InterpolationSearch(T* const arr, size_t size, const T& val)
{
    int begin = 0;
    int end = (size - 1);

    while (begin <= end && val >= arr[begin] && val <= arr[end])
    {
        if (begin == end)
        {
            if (arr[begin] == val) return begin;
            return -1;
        }

        int pos = begin + (((double)(end - begin) /
            (arr[end] - arr[begin])) * (val - arr[begin]));
 
        
        if (arr[pos] == val) return pos;
        
        if (arr[pos] < val){
            begin = pos + 1;
        }
        else{
            end = pos - 1;
        }
    }
    return -1;
}

template<class T>
int InterpolationSearchRec(const T* const arr, int begin, int end, const T& val)
{
    if(begin <= end && val >= arr[begin] && val <= arr[end])
    {
        if (begin == end)
        {
            if (arr[begin] == val) return begin;
            return -1;
        }

        int pos = begin + (((double)(end - begin) /
            (arr[end] - arr[begin])) * (val - arr[begin]));
 
        if (arr[pos] == val) return pos;
        
        if (arr[pos] < val){
            return InterpolationSearchRec(arr, pos + 1, end, val);//begin = pos + 1;
        }
        else{
            return InterpolationSearchRec(arr, begin, pos - 1, val);//end = pos - 1;
        }
    }
    return -1;
}

#endif