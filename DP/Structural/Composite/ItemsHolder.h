#ifndef _ITEMS_HOLDER_H_
#define _ITEMS_HOLDER_H_

#include <vector>
#include <memory>
#include "Item.h"

class ItemsHolder: public IBase
{
public:
    ItemsHolder(/* args */) = default;
    ~ItemsHolder() = default;

    void Add(std::shared_ptr<IBase> val) override
    {
        _data.push_back(std::move(val));
    }

    size_t Price() const override
    {
        size_t res = 0;
        for (size_t i = 0; i < _data.size(); i++)
        {
            if(_data[i]){
                res += _data[i]->Price();
            }
        }
        return res;
    }

private:
    std::vector<std::shared_ptr<IBase>> _data{};
};



#endif