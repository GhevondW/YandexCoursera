#ifndef _INSERTION_SORT_H_
#define _INSERTION_SORT_H_

#include <utility>
#include <vector>

template<class T, class Comparator>
void InsertionSort(std::vector<T>& data, Comparator comp)
{
    size_t size = data.size();
    for (size_t i = 1; i < size; i++)
    {
        if(comp(data[i - 1], data[i]))
        {
            int index = i;
            while (index - 1 >= 0 && comp(data[index - 1], data[index]))
            {
                std::swap(data[index - 1], data[index]);
                --index;
            }
        }
    }
}

#endif