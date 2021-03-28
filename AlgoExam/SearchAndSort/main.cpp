#include <iostream>
#include "Search.h"
#include "Sort.h"

using namespace std;

int main(){
    cout << "Search And Sort" << endl;

    std::vector<int> arr = {6,5,872,7,41,2,49,55,4,1,2,3,46,9,8,58,33,74,65,16};

    // algo::sort::Bubble(arr);
    // algo::sort::Selection(arr);
    // algo::sort::Insertion(arr);
    // algo::sort::Merge(arr);
    // algo::sort::Heap(arr);
    algo::sort::Quick(arr);


    for (int i = 0; i < arr.size(); i++)
    {
        cout<<arr[i]<<", ";
    }
    cout<<endl;
    
    
    for (size_t i = 0; i < arr.size(); i++)
    {
        cout<<"Linear Search value:"<<arr[i]<<" RESULT:"<<(arr[algo::search::Linear(arr, arr[i])] == arr[i])<<endl;
    }
    
    cout<<endl;

    for (size_t i = 0; i < arr.size(); i++)
    {
        cout<<"Binary Search value:"<<arr[i]<<" RESULT:"<<((algo::search::Linear(arr, 5555) == -1) ? "OK" : "Wrong")<<endl;
    }

    for (size_t i = 0; i < arr.size(); i++)
    {
        cout<<"Binary Search value:"<<arr[i]<<" RESULT:"<<((arr.at(algo::search::Linear(arr, arr[i])) == arr.at(i)) ? "OK" : "Wrong")<<endl;
    }
    
    return 0;
}