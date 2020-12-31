#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <iostream>

struct IButton
{
    virtual ~IButton() = default;

    virtual void Draw() = 0;
    virtual void Click() = 0;
};

class WindowsButton : public IButton
{
private:
    /* data */
public:
    WindowsButton(/* args */) = default;
    ~WindowsButton() = default;

    void Draw() override
    {
        std::cout<<"[WIN] Draw"<<std::endl;
    }

    void Click() override
    {
        std::cout<<"[WIN] Click"<<std::endl;
    }

};

class HTMLButton : public IButton
{
private:
    /* data */
public:
    HTMLButton(/* args */) = default;
    ~HTMLButton() = default;

    void Draw() override
    {
        std::cout<<"[HTML] Draw"<<std::endl;
    }

    void Click() override
    {
        std::cout<<"[HTML] Click"<<std::endl;
    }

};


#endif