#include <iostream>
#include "AbstractFactory.h"

using namespace std;

int main()
{
    const bool Mac = false;

    std::shared_ptr<IAbstractFactory> factory{nullptr};
    if(Mac){
        factory = std::make_shared<AbstractFactoryMac>();
    }
    else{
        factory = std::make_shared<AbstractFactoryWindows>();
    }

    auto button = factory->CreateButtonPtr();
    auto image_view = factory->CreateImageViewPtr();

    button->SetText();
    button->SetWidth();

    image_view->SetWidth();
    image_view->SetHeight();

    return 0;
}