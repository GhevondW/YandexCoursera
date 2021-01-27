#ifndef _ISHOP_OBSERVER_H_
#define _ISHOP_OBSERVER_H_

class Shop;

struct IShopObserver
{
    virtual ~IShopObserver() = default;
    virtual void Update(const Shop* shop) const = 0;
};


#endif