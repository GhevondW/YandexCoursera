#ifndef _ABSTR_FACTORY_H_
#define _ABSTR_FACTORY_H_

#include "Button.h"
#include "ImageView.h"
#include <memory>

struct IAbstractFactory
{
    virtual ~IAbstractFactory() = default;

    virtual std::shared_ptr<IButton> CreateButtonPtr(/*Ctor params if needed*/) = 0;
    virtual std::shared_ptr<IImageView> CreateImageViewPtr(/*Ctor params if needed*/) = 0;
};

class AbstractFactoryMac : public IAbstractFactory
{
private:
    /* data */
public:
    AbstractFactoryMac(/* args */) = default;
    ~AbstractFactoryMac() = default;

    std::shared_ptr<IButton> CreateButtonPtr(/*Ctor params if needed*/) override
    {
        return std::make_shared<ButtonMac>();
    }

    std::shared_ptr<IImageView> CreateImageViewPtr(/*Ctor params if needed*/) override
    {
        return std::make_shared<ImageViewMac>();
    }

};

class AbstractFactoryWindows : public IAbstractFactory
{
private:
    /* data */
public:
    AbstractFactoryWindows(/* args */) = default;
    ~AbstractFactoryWindows() = default;

    std::shared_ptr<IButton> CreateButtonPtr(/*Ctor params if needed*/) override
    {
        return std::make_shared<ButtonWindows>();
    }

    std::shared_ptr<IImageView> CreateImageViewPtr(/*Ctor params if needed*/) override
    {
        return std::make_shared<ImageViewWindows>();
    }

};


#endif