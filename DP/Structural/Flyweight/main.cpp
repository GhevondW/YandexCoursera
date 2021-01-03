#include <iostream>
#include "FlyweightFactory.h"
using namespace std;

int main()
{
    cout<<"Flyweight"<<endl;

    auto t1 = FlyweightFactory::GetTexture(TYPE::ONE);
    t1->Draw();
    auto t11 = FlyweightFactory::GetTexture(TYPE::ONE);
    t11->Draw();
    auto t111 = FlyweightFactory::GetTexture(TYPE::ONE);
    t111->Draw();

    auto t2 = FlyweightFactory::GetTexture(TYPE::TWO);
    t2->Draw();
    auto t22 = FlyweightFactory::GetTexture(TYPE::TWO);
    t22->Draw();
    auto t222 = FlyweightFactory::GetTexture(TYPE::TWO);
    t222->Draw();

    auto t3 = FlyweightFactory::GetTexture(TYPE::THREE);
    t3->Draw();
    auto t33 = FlyweightFactory::GetTexture(TYPE::THREE);
    t33->Draw();
    auto t333 = FlyweightFactory::GetTexture(TYPE::THREE);
    t333->Draw();

    return 0;
}