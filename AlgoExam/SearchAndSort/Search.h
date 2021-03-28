#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <vector>

namespace algo
{
    namespace search
    {

        template<class T>
        struct DefaultComparator
        {
            bool operator()(const T& obj1, const T& obj2)
            {
                return obj1 == obj2;
            }
        };

        template<class T, class Comparator = DefaultComparator<T>>
        int Linear(const std::vector<T>& data, const T& value)
        {
            Comparator cmp;
            size_t n = data.size();

            for (int i = 0; i < n; i++)
            {
                if(cmp(data.at(i), value)){
                    return i;
                }
            }

            return -1;
        }

        template<class T>
        int Binary(const std::vector<T>& data, const T& value)
        {
            size_t n = data.size();
            size_t begin = 0;
            size_t end = n - 1;

            while (end >= begin)
            {
                size_t middle = (begin + end) >> 1;
                if(data[middle] == value){
                    return middle;
                }

                if(data[middle] > value){
                    end = middle - 1;
                }
                else{
                    begin = middle + 1;
                }
            }

            return -1;
        }

    };
}; // namespace algo

#endif