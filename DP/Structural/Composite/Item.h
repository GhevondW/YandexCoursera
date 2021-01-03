#ifndef _ITEM_H_
#define _ITEM_H_

#include <utility>
#include <memory>

struct IBase
{
    IBase() = default;
    virtual ~IBase() = default;

    virtual size_t Price() const = 0;
    virtual void Add(std::shared_ptr<IBase> val){}
};

class Item : public IBase
{
public:
    Item(/* args */) = default;
    explicit Item(size_t p)
    :_price(p){}
    ~Item() = default;

    size_t Price() const override
    {
        return _price;
    }

private:
    size_t _price{};
};


#endif