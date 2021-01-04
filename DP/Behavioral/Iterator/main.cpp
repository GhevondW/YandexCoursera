#include <iostream>
#include "Matrix.h"
using namespace std;

int main()
{
    cout<<"Iterator"<<endl;

    Matrix<int, 5> mat{};

    for (size_t i = 0; i < mat.GetSize(); i++)
    {
        for (size_t j = 0; j < mat.GetSize(); j++)
        {
            cout<<mat.At(i, j)<<" ";
        }
        cout<<endl;
    }
    

    return 0;
}