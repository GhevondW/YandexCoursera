#ifndef _REMOTE_H_
#define _REMOTE_H_

#include <memory>
#include "Device.h"

class Remote
{
public:
    Remote(/* args */) = default;
    Remote(std::shared_ptr<IDevice> device)
    :_device(std::move(device))
    {}
    ~Remote() = default;

    void VoliumUp()
    {
        _device->SetVolium(_device->GetVolium() + 1);
    }

    void VoliumDown()
    {
        _device->SetVolium(_device->GetVolium() - 1);
    }

    void ChannelUp()
    {
        _device->SetChannel(_device->GetChannel() + 1);
    }

    void ChannelDown()
    {
        _device->SetChannel(_device->GetChannel() - 1);
    }

    void TogglePower()
    {
        if(_device->IsEnabled()){
            _device->Disable();
        }
        else{
            _device->Enable();
        }
    }

private:
    std::shared_ptr<IDevice> _device{nullptr};
};



#endif