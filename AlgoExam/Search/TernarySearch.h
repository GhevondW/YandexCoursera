#ifndef _TERNARY_SEARCH_H_
#define _TERNARY_SEARCH_H_

#include <utility>
#include "Defines.h"

template<class T>
int TernarySearch(const T* const arr, int begin, int end, const T& val) 
{ 
   if (end >= begin) 
   { 
        int mid1 = begin + (end - begin)/3; 
        int mid2 = mid1 + (end - begin)/3; 
  
        // If x is present at the mid1 
        if (arr[mid1] == val)  return mid1; 
  
        // If x is present at the mid2 
        if (arr[mid2] == val)  return mid2; 
  
        // If x is present in left one-third 
        if (arr[mid1] > val) return TernarySearch(arr, begin, mid1-1, val); 
  
        // If x is present in right one-third 
        if (arr[mid2] < val) return TernarySearch(arr, mid2+1, end, val); 
  
        // If x is present in middle one-third 
        return TernarySearch(arr, mid1+1, mid2-1, val); 
   } 
   return -1; 
}

#endif