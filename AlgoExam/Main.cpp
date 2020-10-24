#include "Algo.h"
#include <iostream>
#include "List.h"
#include <vector>

using namespace std;

extern void print(float);
extern void print(int);

struct Move
{
	Move() = default;
	Move(Move&&) = default;
	Move& operator=(Move&&) = default;

	Move(const Move&) = delete;
	Move& operator=(const Move&) = delete;
	string _data;
};

struct CopyObj
{
	CopyObj()
	{
		cout << "CopyObj Def ctor" << endl;
	};
	//CopyObj(CopyObj&&) = delete;
	//CopyObj& operator=(CopyObj&&) = delete;

	CopyObj(const CopyObj& other)
		:_data(other._data)
	{
		cout << "CopyObj Copy ctor" << endl;
	}
	CopyObj& operator=(const CopyObj& other)
	{
		cout << "CopyObj = oper" << endl;
		_data = other._data;
		return *this;
	}
	string _data{};
};

struct All
{
	All() = default;
	All(All&&) = default;
	All& operator=(All&&) = default;

	All(const All&) = default;
	All& operator=(const All&) = default;
	string _data;
};

int main()
{

	Move m{};
	CopyObj c{};
	All a{};

	/*
	algo::List<CopyObj> list;

	list.PushBack(c);
	list.PushBack(CopyObj{});
	*/

	algo::List<int> list;

	list.PushBack(4);
	list.PushBack(3);
	list.PushBack(2);

	auto res = list.Find(3);



	return 0;
}


void print(float f)
{
	cout << f << endl;
}


void print(int i)
{
	cout << i << endl;
}
