//: C11:HowMany.cpp
// A class that counts its objects
#include <fstream>
#include <string>
#include <iostream>
#include "LinkedList.h"
using namespace std;

const extern int X;

int main() {
	algo::LinkedList<string> ll;

	ll.PushBack("1");
	ll.PushBack("2");
	ll.PushBack("3");
	auto ret = ll.PushBack("4");
	auto ret_begin = ll.PushFront("0");

	auto ret1 = ll.PopBack();

	return 0;
} ///:~