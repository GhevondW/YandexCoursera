#ifndef _DIALOG_H_
#define _DIALOG_H_

#include <memory>
#include "Button.h"

struct IDialog
{
    virtual ~IDialog() = default;

    virtual void Draw()
    {
        auto button = CreateButton();
        button->Draw();
        button->Click();
    }

    virtual std::shared_ptr<IButton> CreateButton() = 0;
};

class WindowsDialog : public IDialog
{
private:
    /* data */
public:
    WindowsDialog(/* args */) = default;
    ~WindowsDialog() = default;

    std::shared_ptr<IButton> CreateButton() override
    {
        return std::make_shared<WindowsButton>(); 
    }

};

class HTMLDialog : public IDialog
{
private:
    /* data */
public:
    HTMLDialog(/* args */) = default;
    ~HTMLDialog() = default;

    std::shared_ptr<IButton> CreateButton() override
    {
        return std::make_shared<HTMLButton>(); 
    }

};

#endif /*_DIALOG_H_*/