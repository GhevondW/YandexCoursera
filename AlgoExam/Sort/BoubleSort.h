#ifndef _BOUBLE_SORT_H_
#define _BOUBLE_SORT_H_

#include <utility>

template<class T, class Comparator>
void BoubleSort(std::vector<T>& data, Comparator comp)
{
    size_t size = data.size();
    for (size_t i = 0; i < size - 1; i++)
    {
        bool swap = false;
        for (size_t j = 0; j < size - i - 1; j++)
        {
            if(comp(data[j], data[j + 1])){
                std::swap(data[j], data[j + 1]);
                swap = true;
            }
        }
        
        if(!swap) break;
    }
}

#endif