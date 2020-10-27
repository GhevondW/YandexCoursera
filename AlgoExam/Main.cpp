#include "Algo.h"
#include <iostream>
#include "List.h"
#include <vector>

using namespace std;


int main()
{

	std::vector<int> data = {9,2,1,3,6,8,7,4,5,2,1,5,6,8,5,4,1,2,3,6,9,8,5,4,7,5,2,1,3,7};

	//algo::BubbleSort(data, [](int a, int b) {return a > b; });
	//algo::InsertionSort(data, [](int a, int b) {return a > b; });
	algo::SelectionSort(data, [](int a, int b) {return a > b; });

	auto index = algo::BinarySearch(data, 5);

	algo::List<int> list;

	list.PushBack(4);
	list.PushBack(3);
	list.PushBack(2);

	auto res = list.Find(4);

	list.Insert(res, 8);
	list.Delete(res);
	list.PopFront();


	cout << list.Size() << endl;

	algo::List<int>::Printer p;
	p(list);


	return 0;
}