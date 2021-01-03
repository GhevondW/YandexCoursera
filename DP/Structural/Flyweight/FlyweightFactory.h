#ifndef _Flyweight_Factory_h_
#define _Flyweight_Factory_h_

#include "Texture.h"
#include <vector>
#include <memory>

class FlyweightFactory
{
private:
    FlyweightFactory(/* args */);
    

public:
    ~FlyweightFactory() = default;
    static std::shared_ptr<Texture> GetTexture(TYPE type)
    {
        std::shared_ptr<Texture> ret{nullptr};
        if(_data[(size_t)type] == nullptr){
            ret = std::make_shared<Texture>(type);
            _data[(size_t)type] = ret;
            return ret;
        }
        ret = _data[(size_t)type];
        return ret;
    }

private:
    static std::vector<std::shared_ptr<Texture>> _data;
};

std::vector<std::shared_ptr<Texture>> FlyweightFactory::_data = std::vector<std::shared_ptr<Texture>>(3, nullptr);

#endif