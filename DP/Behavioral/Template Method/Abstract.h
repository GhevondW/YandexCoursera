#ifndef _ABSTRACT_H_
#define _ABSTRACT_H_

#include <iostream>

class Abstract
{
public:
	Abstract() = default;
	virtual ~Abstract() = default;

	void DoTask();

protected:

	void Action1();
	void Action2();

	virtual void Option1() = 0;
	virtual void Option2() = 0;

	virtual void Option3();
	virtual void Option4();

};

void Abstract::DoTask() {

	long long ll = (long long)this;

	this->Action1();
	this->Action2();
	this->Option1();
	this->Option2();
	this->Option3();
	this->Option4();
}

void Abstract::Action1() {
	std::cout << "A1" << std::endl;
}

void Abstract::Action2() {
	std::cout << "A2" << std::endl;
}

void Abstract::Option3() {
	std::cout << "Abstract O3" << std::endl;
}

void Abstract::Option4() {
	std::cout << "Abstract O4" << std::endl;
}

#endif // !_ABSTRACT_H_

