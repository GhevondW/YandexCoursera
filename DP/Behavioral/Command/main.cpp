#include <iostream>
#include "BasicExample.h"
#include "Example.h"
using namespace std;

 
/*The test class or client*/
int main() 
{
    cout<<"Command"<<endl;
    /* Basic Example
    Light lamp;
    FlipUpCommand switchUp(lamp);
    FlipDownCommand switchDown(lamp);

    Switch s(switchUp, switchDown);
    s.flipUp();
    s.flipDown();
    */

    Invoker *invoker = new Invoker;
    invoker->SetOnStart(new SimpleCommand("Say Hi!"));
    Receiver *receiver = new Receiver;
    invoker->SetOnFinish(new ComplexCommand(receiver, "Send email", "Save report"));
    invoker->DoSomethingImportant();

    delete invoker;
    delete receiver;

    return 0;
}