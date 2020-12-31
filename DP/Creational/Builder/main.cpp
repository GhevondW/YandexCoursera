#include <iostream>
#include "Car.h"
using namespace std;

int main()
{
	std::cout << "---Builder---" << std::endl;

	auto* car = Car::Make()
		.SetAI(true)
		.SetChip(true)
		.SetColor(Color::BLACK)
		.SetClass(CarClass::RS6)
		.SetHp(1000)
		.SetNm(1250)
		.SetGPS(true)
		.SetStage(Stage::STAGE2)
		.SetDoorsCount(5)
		.Build();


    delete car;
	return 0;
}