#ifndef _SELECTION_SORT_H_
#define _SELECTION_SORT_H_

#include <vector>
#include <utility>

template<class T, class Comparator>
int FindIndex(const std::vector<T>& data, size_t begin, size_t end, Comparator comp)
{
    size_t index = begin;
    for (size_t i = begin + 1; i <= end; i++)
    {
        if(comp(data[index], data[i])){
            index = i;
        }
    }
    return index;
}

template<class T, class Comparator>
void SelectionSort(std::vector<T>& data, Comparator comp)
{
    size_t size = data.size();
    for (size_t i = 0; i < size - 1; i++)
    {
        int index = FindIndex(data, i, size - 1, comp);
        std::swap(data[i], data[index]);
        // T tmp = std::move(data[i]);
        // data[i] = std::move(data[index]);
        // data[index] = std::move(tmp);
    }
}

#endif