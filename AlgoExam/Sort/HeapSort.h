#ifndef _HEAP_SORT_H_
#define _HEAP_SORT_H_

#include <utility>
#include "Defines.h"
#include <vector>

template<class T, class Comparator>
void Heapify(std::vector<T>& data, const size_t size, const size_t index, Comparator comp)
{
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;
    size_t current_head = index;

    if(left < size && comp(data[current_head], data[left])){
        current_head = left;
    }

    if(right < size && comp(data[current_head], data[right])){
        current_head = right;
    }

    if(current_head != index){
        std::swap(data[index], data[current_head]);

        Heapify(data, size, current_head, comp);
    }

}

template<class T, class Comparator>
void HeapSort(std::vector<T>& data, Comparator comp)
{
    for (int i = data.size() / 2 - 1; i >= 0; i--){
        Heapify(data, data.size(), i, comp);
    }

    for (int i = data.size() - 1; i > 0; i--) {
        // Move current root to end
        std::swap(data[0], data[i]);
 
        // call max heapify on the reduced heap
        Heapify(data, i, 0, comp);
    }
}

#endif