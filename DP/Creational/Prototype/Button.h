#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <functional>
#include <iostream>

using Callback = std::function<void(int)>;

struct IButton
{

    IButton() = default;
    IButton(int w, int h, const std::string& text)
    :_width(w),
    _height(h),
    _text(text)
    {}

    IButton(const IButton& other)
    :_width(other._width),
    _height(other._height),
    _text(other._text)
    {}

    virtual ~IButton() = default;

    virtual auto Click(Callback)    -> void = 0;
    virtual auto PrintWidth()         -> void = 0;
    virtual auto PrintHeight()        -> void = 0;
    virtual auto PrintText()          -> void = 0;

    // this method provides the prototyping functionality for each subclass
    virtual auto Clone() const      -> std::shared_ptr<IButton> = 0; 

    int GetWidth() const { return _width; }
    int GetHeight() const { return _height; }
    const std::string& GetText() const { return _text; }

protected:
    int         _width{};
    int         _height{};
    std::string _text{};
};

class ButtonMac : public IButton
{
private:
    /* data */
public:
    ButtonMac(/* args */) = default;
    ButtonMac(int w, int h, std::string text)
    :IButton(w, h, text)
    {}

    ButtonMac(const ButtonMac& other)
    :IButton(other)
    {}

    ~ButtonMac() = default;

    void Click(Callback cb) override 
    {
        cb(12);
        std::cout<<"[BTN Mac] Click"<<std::endl;
    }

    void PrintWidth() override 
    {
        std::cout<<"[BTN Mac] PrintWidth:"<<_width<<std::endl;
    }

    void PrintHeight() override 
    {
        std::cout<<"[BTN Mac] PrintHeight:"<<_height<<std::endl;
    }

    void PrintText() override 
    {
        std::cout<<"[BTN Mac] PrintText:"<<_text<<std::endl;
    }


    std::shared_ptr<IButton> Clone() const override
    {
        return std::make_shared<ButtonMac>(*this);
    }

};

class ButtonWindows: public IButton
{
private:
    /* data */
public:
    ButtonWindows(/* args */) = default;
    ButtonWindows(int w, int h, std::string text)
    :IButton(w, h, text)
    {}

    ButtonWindows(const ButtonMac& other)
    :IButton(other)
    {}

    ~ButtonWindows() = default;

    void Click(Callback cb) override 
    {
        cb(12);
        std::cout<<"[BTN Windows] Click"<<std::endl;
    }

    void PrintWidth() override 
    {
        std::cout<<"[BTN Windows] PrintWidth:"<<_width<<std::endl;
    }

    void PrintHeight() override 
    {
        std::cout<<"[BTN Windows] PrintHeight:"<<_height<<std::endl;
    }

    void PrintText() override 
    {
        std::cout<<"[BTN Windows] PrintText:"<<_text<<std::endl;
    }

    std::shared_ptr<IButton> Clone() const override
    {
        return std::make_shared<ButtonWindows>(*this);
    }

};

#endif /* _BUTTON_H_ */