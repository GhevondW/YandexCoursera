#include <iostream>
#include "AbstractFactory.h"

using namespace std;

int main()
{
    cout<<"Prototype"<<endl;
    const bool Mac = true;
    std::shared_ptr<IAbstractFactory> factory{};
    if(Mac){
        factory = std::make_shared<AbstractFactoryMac>();
    }
    else{
        factory = std::make_shared<AbstractFactoryWindows>();
    }
    
    std::shared_ptr<IButton> button = factory->CreateButtonPtr(300, 50, "Click Me");

    button->Click([](int){});
    button->PrintWidth();
    button->PrintHeight();
    button->PrintText();

    std::shared_ptr<IButton> clone = button->Clone();

    clone->PrintWidth();
    clone->PrintHeight();
    clone->PrintText();

    return 0;
}