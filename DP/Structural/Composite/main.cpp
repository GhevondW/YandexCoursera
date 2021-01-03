#include <iostream>
#include "ItemsHolder.h"
using namespace std;

int main()
{
    cout<<"Composite"<<endl;

    std::shared_ptr<IBase> holder = std::make_shared<ItemsHolder>();
    std::shared_ptr<IBase> inner = std::make_shared<ItemsHolder>();

    inner->Add(std::make_shared<Item>(5));
    inner->Add(std::make_shared<Item>(4));
    inner->Add(std::make_shared<Item>(3));
    inner->Add(std::make_shared<Item>(16));

    cout<<inner->Price()<<endl;

    inner->Add(std::make_shared<Item>(1));
    holder->Add(std::move(inner));

    cout<<holder->Price()<<endl;

    return 0;
}