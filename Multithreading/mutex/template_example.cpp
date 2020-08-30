#include <iostream>
#include <condition_variable>
#include <mutex>
#include <atomic>

template<class T>
struct Example
{

    Example() = default;
    ~Example() = default;

    template<class... Args>
    void SetData(Args&&... args)
    {
        data = T(args...);
    }

    void PrintData() const
    {
        data.Print();
    }

    T data;
};

class A
{
private:
    int _a{};
    double _b{};
public:
    A() = default;
    A(int a, double b):_a(a),_b(b){};
    ~A() = default;

    void Print() const
    {
        std::cout<<_a<<":"<<_b<<std::endl;
    }
};



int main()
{

    std::cout<<"vtemplate example"<<std::endl;

    Example<A> ex{};

    ex.SetData();
    ex.PrintData();
    ex.SetData(4, 3.5);
    ex.PrintData();

    return 0;
}