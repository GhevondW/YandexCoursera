#ifndef _SHOP_H_
#define _SHOP_H_

#include <vector>
#include "IShopObserver.h"

class Shop
{
private:
    size_t                      _discount{};
    std::vector<IShopObserver*> _subscribed{};
public:
    Shop() = default;
    ~Shop() = default;

    void SetDiscount(size_t val)
    {
        _discount = val < 100 ? val : _discount; 
        _Notify();
    }
    size_t GetDiscount() const { return _discount; }

    void Subscribe(IShopObserver* user)
    {
        if(user != nullptr){
            _subscribed.push_back(user);
        }
    }

private:

    void _Notify() const{
        for (size_t i = 0; i < _subscribed.size(); i++)
        {
            _subscribed[i]->Update(this);
        }
        
    }

};

#endif