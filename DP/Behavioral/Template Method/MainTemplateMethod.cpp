#include <iostream>
#include "Impl.h"

using namespace std;

int main() {
	cout << "Hello World" << endl;

	Impl1* a = new Impl1();
	Impl2* b = new Impl2();

	long long la = (long long)a;
	long long lb= (long long)b;

	a->DoTask();
	b->DoTask();


	return 0;
}