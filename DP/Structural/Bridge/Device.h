#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <utility>
#include <iostream>

struct IDevice
{
    IDevice() = default;
    virtual ~IDevice() = default;

    virtual bool IsEnabled() const = 0;
    virtual void Enable() = 0;
    virtual void Disable() = 0;
    virtual void SetVolium(size_t) = 0;
    virtual size_t GetVolium() const = 0;
    virtual void SetChannel(size_t) = 0;
    virtual size_t GetChannel() const = 0;
};

class TV : public IDevice
{
private:
    /* data */
public:
    TV() = default;
    ~TV() = default;

    bool IsEnabled() const
    {
        std::cout<<"[TV] IsEnabled"<<std::endl;
        return _isEnabled;
    }

    void Enable()
    {
        std::cout<<"[TV] Enable"<<std::endl;
        _isEnabled = true;
    }

    void Disable()
    {
        std::cout<<"[TV] Disable"<<std::endl;
        _isEnabled = false;
    }

    void SetVolium(size_t v)
    {
        std::cout<<"[TV] SetVolium"<<std::endl;
        _volium = v;
    }

    size_t GetVolium() const
    {
        std::cout<<"[TV] GetVolium"<<std::endl;
        return _volium;
    }

    void SetChannel(size_t c)
    {
        std::cout<<"[TV] SetChannel"<<std::endl;
        _channel = c;
    }

    size_t GetChannel() const
    {
        std::cout<<"[TV] GetChannel"<<std::endl;
        return _channel;
    }


private:
    bool _isEnabled{};
    size_t _volium{};
    size_t _channel{};
};

class Radio : public IDevice
{
private:
    /* data */
public:
    Radio() = default;
    ~Radio() = default;

    bool IsEnabled() const
    {
        std::cout<<"[Radio] IsEnabled"<<std::endl;
        return _isEnabled;
    }

    void Enable()
    {
        std::cout<<"[Radio] Enable"<<std::endl;
        _isEnabled = true;
    }

    void Disable()
    {
        std::cout<<"[Radio] Disable"<<std::endl;
        _isEnabled = false;
    }

    void SetVolium(size_t v)
    {
        std::cout<<"[Radio] SetVolium"<<std::endl;
        _volium = v;
    }

    size_t GetVolium() const
    {
        std::cout<<"[Radio] GetVolium"<<std::endl;
        return _volium;
    }

    void SetChannel(size_t c)
    {
        std::cout<<"[Radio] SetChannel"<<std::endl;
        _channel = c;
    }

    size_t GetChannel() const
    {
        std::cout<<"[Radio] GetChannel"<<std::endl;
        return _channel;
    }


private:
    bool _isEnabled{};
    size_t _volium{};
    size_t _channel{};
};


#endif