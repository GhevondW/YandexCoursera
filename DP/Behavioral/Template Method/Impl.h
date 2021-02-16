#ifndef _IMPL_H_
#define _IMPL_H_

#include "Abstract.h"

class Impl1 : public Abstract
{
public:
	Impl1() = default;
	~Impl1() = default;

protected:
	virtual void Option1() override;
	virtual void Option2() override;
};

void Impl1::Option1() {
	std::cout << "I1 O1" << std::endl;
}

void Impl1::Option2() {
	std::cout << "I1 O2" << std::endl;
}

class Impl2 : public Abstract
{
public:
	Impl2() = default;
	~Impl2() = default;

protected:
	virtual void Option1() override;
	virtual void Option2() override;
	virtual void Option3() override;
	virtual void Option4() override;
};

void Impl2::Option1() {
	std::cout << "I2 O1" << std::endl;
}

void Impl2::Option2() {
	std::cout << "I2 O2" << std::endl;
}

void Impl2::Option3() {
	std::cout << "I2 O3" << std::endl;
}

void Impl2::Option4() {
	std::cout << "I2 O4" << std::endl;
}

#endif // !_IMPL_H_
