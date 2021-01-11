#include <iostream>
#include "LinearSearch.h"
#include "BinarySearch.h"
#include "JumpSearch.h"
#include "InterpolationSearch.h"
#include "ExponentialSearch.h"
#include "TernarySearch.h"
using namespace std;

int main()
{
    cout<<"Search"<<endl;

    int arr[] = { 2, 3, 4, 10, 40, 44, 44, 50, 50, 51, 99 }; 

    int x{};
    while (x != -1)
    {
        cout<<"X=:";
        cin >> x;
        cout << ((arr[TernarySearch(arr, 0, SIZE(arr), x)] == x) ? "TRUE" : "FALSE") << endl;
        cout<<'\n';
    }

    cout<<"End"<<endl;

    return 0;
}