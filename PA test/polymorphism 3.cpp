#include <cassert>
#include <stdexcept>
#include <string>

struct Base {
    Base* clone() {
        throw std::runtime_error("You should implement this");
    }
};

struct Derived : Base {
    std::string data;
    
    Derived(const std::string &dataIn) : data(dataIn) {}
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

