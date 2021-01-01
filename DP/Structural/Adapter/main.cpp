#include <iostream>
#include "Element.h"
using namespace std;

int main()
{
    cout << "Adapter" << endl;

    auto elem = Element::Make()
    .SetFirstName("Ghevond")
    .SetLastName("Gevorgyan")
    .SetGroupName("MTT-919")
    .SetRating(98)
    .SetPubCount(1)
    .BuildPtr();

    elem->Print();

    return 0;
}