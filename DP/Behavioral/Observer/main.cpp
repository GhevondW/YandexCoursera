#include <iostream>
#include "Shop.h"
#include "User.h"
#include <memory>
using namespace std;

int main()
{

    cout<<"Observer"<<endl;

    std::shared_ptr<Shop> shop = std::make_shared<Shop>();
    std::shared_ptr<IShopObserver> user1 = std::make_shared<User>("Ghevond");
    std::shared_ptr<IShopObserver> user2 = std::make_shared<User>("Aram");
    std::shared_ptr<IShopObserver> user3 = std::make_shared<User>("Levon");

    shop->Subscribe(user1.get());
    shop->Subscribe(user2.get());
    shop->Subscribe(user3.get());


    shop->SetDiscount(12);


    return 0;
}