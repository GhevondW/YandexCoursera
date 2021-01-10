#include <cassert>
#include <stdexcept>
#include <string>

struct Base {
    Base() = default;
    virtual ~Base() = default;
    virtual Base* clone() = 0;
};

struct Derived : public Base {
    std::string data{};
    
    Derived() = default;
    Derived(const std::string &dataIn) : data(dataIn) {}
    Derived(const Derived& other)
    :data(other.data)
    {}
    Derived(Derived&& other)
    :data(std::move(other.data))
    {}
    ~Derived() = default;

    Base* clone() override
    {
        return new Derived(*this);
    }
};

int main(int argc, const char * argv[]){
    /*
     Implement and correct clone() method on Base and Derived that will copy object and after that fix memory leak.
     */
    
    Derived d("Hello world!");
    Base *b = &d;
    Base *cloned = b->clone();
    assert(((Derived*)cloned)->data == "Hello world!");
    delete cloned;
    return 0;
}