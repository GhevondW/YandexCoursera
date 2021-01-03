#include <iostream>
#include "Device.h"
#include "Remote.h"

using namespace std;

int main()
{
    cout<<"Bridge"<<endl;

#if 0
    std::shared_ptr<Remote> remote = std::make_shared<Remote>
    (
        std::make_shared<TV>()
    );
#else
    std::shared_ptr<Remote> remote = std::make_shared<Remote>
    (
        std::make_shared<Radio>()
    );
#endif

    remote->ChannelDown();
    remote->ChannelUp();
    remote->VoliumDown();
    remote->VoliumUp();
    remote->TogglePower();

    return 0;
}