#ifndef _USER_H_
#define _USER_H_

#include "IShopObserver.h"
#include "Shop.h"
#include <iostream>
#include <string>

class User : public IShopObserver
{
private:
    /* data */
    std::string _name{};
public:
    User(/* args */) = default;
    User(const std::string& name):_name(name)
    {}
    ~User() = default;

    void Update(const Shop* shop) const override
    {
        std::cout<<"User:"<<_name<<" Discount:"<<shop->GetDiscount()<<std::endl;
    }

};


#endif