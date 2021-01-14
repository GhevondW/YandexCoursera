#include <iostream>
#include "SelectionSort.h"
#include "BoubleSort.h"
#include "profile.h"
#include "InsertionSort.h"
#include "Defines.h"
#include "HeapSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
using namespace std;

template<class T>
bool CompareLess(const T& a, const T& b)
{
    return a < b;
}

template<class T>
bool CompareMore(const T& a, const T& b)
{
    return a > b;
}

int main()
{
    cout<<"Sort"<<endl;

    std::vector<int> arr = {12, 11, 13, 5, 6, 7, 19, 1, 22, 23};

    size_t s = arr.size();

    // for (size_t i = 0; i < s; ++i)
    // {
    //     arr.emplace_back(i);
    // }
    
    // { LOG_DURATION("Speed HeapSort");
        MergeSort(arr, CompareMore<int>);
    // }

    for (size_t i = 0; i < MIN(s, 40); i++)
    {
        cout<<(arr[i])<<", ";
    }
    cout<<endl;

    return 0;
}