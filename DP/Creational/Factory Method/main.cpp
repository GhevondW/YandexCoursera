#include <iostream>
#include "Dialog.h"

using namespace std;

int main()
{
    cout<<"Factory Method"<<endl;

    std::shared_ptr<IDialog> dialog{new WindowsDialog()};
    
    dialog->Draw();

    return 0;
}