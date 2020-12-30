#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <functional>
#include <iostream>

using Callback = std::function<void(int)>;

struct IButton
{
    virtual ~IButton() = default;
    virtual void Click(Callback) = 0;
    virtual void SetWidth() = 0;
    virtual void SetHeight() = 0;
    virtual void SetText() = 0;
};

class ButtonMac : public IButton
{
private:
    /* data */
public:
    ButtonMac(/* args */) = default;
    ~ButtonMac() = default;

    void Click(Callback cb) override 
    {
        cb(12);
        std::cout<<"[BTN Mac] Click"<<std::endl;
    }

    void SetWidth() override 
    {
        std::cout<<"[BTN Mac] SetWidth"<<std::endl;
    }

    void SetHeight() override 
    {
        std::cout<<"[BTN Mac] SetHeight"<<std::endl;
    }

    void SetText() override 
    {
        std::cout<<"[BTN Mac] SetText"<<std::endl;
    }

};

class ButtonWindows: public IButton
{
private:
    /* data */
public:
    ButtonWindows(/* args */) = default;
    ~ButtonWindows() = default;

    void Click(Callback cb) override 
    {
        cb(12);
        std::cout<<"[BTN Windows] Click"<<std::endl;
    }

    void SetWidth() override 
    {
        std::cout<<"[BTN Windows] SetWidth"<<std::endl;
    }

    void SetHeight() override 
    {
        std::cout<<"[BTN Windows] SetHeight"<<std::endl;
    }

    void SetText() override 
    {
        std::cout<<"[BTN Windows] SetText"<<std::endl;
    }

};

#endif /* _BUTTON_H_ */